
/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <regex.h>
#include<pwd.h>
#include<fcntl.h>
#include "command.h"

SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numberOfAvailableArguments * sizeof( char * ) );
	}

	if(argument[0] == '.' && argument[1] == '/')
	{
		char * newArg = (char*)malloc((strlen(argument) - 2)*sizeof(char));
		strncpy(newArg, argument+2, strlen(argument) - 1);
		//free(argument);
		argument = newArg;
	}

	char* dir;
	if(argument[0] == '~'){
		if(argument[1] != '/' && argument[1] != '\0')
		{
			char* slash = strchr(argument, '/');
			int length = strlen(argument)+1;
			char* user;
			if(slash == NULL)
			{
				slash = strstr(argument, " ");
				if(slash == NULL)
				{
					user = (char*)malloc(length);
					strcpy(user, argument+1);
				}
				else
				{
					length = slash-(argument+1);
					user = (char*)malloc(length);
					strncpy(user, argument+1, length);
				}
			}
			else
			{
				length = slash-(argument+1);
				user = (char*)malloc(length);
				strncpy(user, argument+1, length);
			}
			struct passwd* dir_ent = getpwnam(user);
			dir = (char*)malloc(length);
			strcpy(dir, dir_ent->pw_dir);
			if(slash)
				strcat(dir, slash);
			argument = dir;
		}
		else
		{
			dir = getenv("HOME");
			strcpy(argument, dir);
		}
		
	}
	
	
	// Matches: ${....}
	// Example: ${A}
	
	char* regEx = (char*)"^.*\\$\\{[^}]*\\}.*$";
	regex_t buffer;
	int res = regcomp(&buffer, regEx, REG_EXTENDED);
	if(res != 0){
		exit(-1);
	}
	regmatch_t match;
	
	while(!regexec(&buffer, argument, 1, &match, 0)){
	
			//To Do: Expand any matching ${...} into the proper environment variable
			//See man getenv()
			//Also Tilde Expansion
		char * expArg = (char*)calloc(1024,sizeof(char));
		char * temp = (char*)calloc(128,sizeof(char));
		strncpy(expArg, argument, match.rm_so);
		strncpy(temp, argument+match.rm_so+2,((match.rm_eo-1)-(match.rm_so+2)));
		char * f = getenv(temp);
		if (f!=NULL){
			strcat(expArg, f);
		}
		
		strcat(expArg, argument+match.rm_eo);
		expArg[match.rm_so+((match.rm_eo)-(match.rm_so+1))+(strlen(argument)-match.rm_eo)+2] = '\0';
		
		//free(argument);
		argument = expArg;
	}
	
	
	_arguments[ _numberOfArguments ] = argument;

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}
void SimpleCommand::insertSortedArgument(char * argument)
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numberOfAvailableArguments * sizeof( char * ) );
	}

	if(argument[0] == '.' && argument[1] == '/')
	{
		char * newArg = (char*)malloc((strlen(argument) - 2)*sizeof(char));
		strncpy(newArg, argument+2, strlen(argument) - 1);
		argument = newArg;
	}
	// loop over elements of arguments for each element compare the argument that was passed in to that in the array, if its greater then add it at that index, if it less or equal, we keep going.
	/* arguments = {c, d, e}
         * insert a
         * {a, c, d, e}
         * insert z
         * {a, c, d, e, z} */
	int i = 0;

	for (i=1; i<_numberOfArguments; i++){
		if(strcmp(argument, _arguments[i]) < 0){
			for (int k = _numberOfArguments-1; k >= i; k--){
				_arguments[k+1] = _arguments[k];
			}
			break;
		}
		
	}
	_arguments[i] = argument;

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;


	_outFileCounter = 0;
	_inFileCounter = 0;
	_errFileCounter = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}
	if (_outFile &&(_outFile == _errFile)){
		free(_outFile);
	}
	else {
		if ( _outFile ) {
			free( _outFile );
		}

		if ( _errFile ) {
			free( _errFile );
		}
	}
	if ( _inputFile ) {
		free( _inputFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;


	_outFileCounter = 0;
	_inFileCounter = 0;
	_errFileCounter = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
	
}

void
Command::execute()
{
	
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0) {
		prompt();
		return;
	}
	if(!strcmp(_simpleCommands[0]->_arguments[0], "cd")){
		if(_simpleCommands[0]->_arguments[1] == NULL){
			chdir(getpwuid(getuid())->pw_dir);
		}
		else{
			chdir(_simpleCommands[0]->_arguments[1]);
		}
		clear();
		prompt();
		return;
	}

	if(_outFileCounter > 1) {
		printf("Ambiguous output redirect\n");
	}
	if(_inFileCounter > 1) {
		printf("Ambiguous input redirect\n");
	}
	if(_errFileCounter > 1) {
		printf("Ambiguous error redirect\n");
	}

	if(strcmp(_simpleCommands[0]->_arguments[0], "exit") == 0){
		exit(0);
	}

	// Print contents of Command data structure
	//print();

	int out = dup(1);
	int in = dup(0);
	int err = dup(2);

	int fdpipe[2];
	int pid;
	int infd, outfd, piping;
	int n = _numberOfSimpleCommands;
	piping = 0;

	if (_errFile && _append )
	{
		dup2(open(_errFile, O_WRONLY|O_APPEND|O_CREAT, 0600), 2);
	}
	else if (_errFile)
	{
		dup2(open(_errFile, O_WRONLY|O_TRUNC|O_CREAT, 0600), 2);
	}
	else
	{
		dup2(err, 2);
	}
	close(err);
	//fprintf(stderr, "inputFile: %s\n", _inputFile);
	if(_inputFile)
		infd = open(_inputFile, O_RDONLY);
	else
		infd = dup(in);
	//fprintf(stderr, "Number of simple commands: %d\n", _numberOfSimpleCommands);
	for(int i=0; i<n; i++)
	{
		//fprintf(stderr, "\n---------------------------------------\nInput: %d\n Command: %d\n", infd, i);
		dup2(infd, 0);
		close(infd);
		if (i+1 == n)
		{
			//fprintf(stderr, "outFile: %s\n", _outFile);
			//fprintf(stderr, "_append: %d\n", _append);
			// Output to file if there is one
			if(_outFile && _append)
			{
				outfd = open(_outFile, O_WRONLY|O_APPEND|O_CREAT, 0600);
			}
			else if (_outFile)
			{
				outfd = open(_outFile, O_WRONLY|O_TRUNC|O_CREAT, 0600);
			}
			else
			{
				// Set to Stdout
				outfd = dup(out);
			}
		}
		else
		{
			//fprintf(stderr, "Making a pipe!\n");
			// Create pipe
			pipe(fdpipe);
			// Stdout to write end of pipe
			outfd = fdpipe[1];
			//fprintf(stderr, "Write end of pipe: %d\n", outfd);
			// Stdinput to read end of pipe
			infd = fdpipe[0];
			//fprintf(stderr, "Read end of pipe: %d\n", infd);
			piping = 1;
		}
		//fprintf(stderr, "Output FD: %d\n", outfd);
		dup2(outfd, 1);
		close(outfd);

		
			
		//fprintf(stderr, "Calling: %s\n", _simpleCommands[i]->_arguments[0]);

		

		if(!strcmp(_simpleCommands[i]->_arguments[0], "setenv")){
			char* A = _simpleCommands[i]->_arguments[1];
			char* B = _simpleCommands[i]->_arguments[2];
			char* target = (char*)malloc(sizeof(char)*(strlen(A)+strlen(B)+1));
			strcpy(target, A);
			strcat(target, "=");
			strcat(target, B);
			putenv(target);
		}
		else if(!strcmp(_simpleCommands[i]->_arguments[0], "unsetenv")){
			char* A = _simpleCommands[i]->_arguments[1];
			unsetenv(A);
		}
		else{
			pid = fork();
			if ( pid == -1 ) {
				perror( "shell: fork\n");
				exit( 2 );
			}

			if (pid == 0) {
				//Child
				if(piping)
				{
					close(fdpipe[0]);
					close(fdpipe[1]);
				}
				if(strcmp(_simpleCommands[i]->_arguments[0], "printenv")==0){
					int current = 0;
					while(environ[current] != NULL){
						printf("%s\n", environ[current]);
						current++;
					}
					exit(0);
				}
				// You can use execvp() instead if the arguments are stored in an array
				execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);

				// exec() is not suppose to return, something went wrong
				perror( "fork: error");
				exit( 2 );
			}
		}
		
	}
	if(!_background)
	{
		waitpid(pid, NULL, 0);
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);

	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	prompt();
}

// Shell implementation
void sigintHandle(int sig){
	Command::_currentCommand.clear();
	printf("\n");
	Command::_currentCommand.prompt();
	
}
void sigChildHandle(int sig){
	wait3(0,0,NULL);
	while(waitpid(-1, NULL, WNOHANG) >0);
}
void
Command::prompt()
{
	if(isatty(0))
		printf("myshell>");
	fflush(stdout);
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

extern main()
{
	struct sigaction sigInt;
	sigInt.sa_handler = sigintHandle;
	sigemptyset(&sigInt.sa_mask);
	sigInt.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sigInt, NULL);
	
	sigInt.sa_handler = sigChildHandle;
	sigemptyset(&sigInt.sa_mask);
	sigaction(SIGCHLD, &sigInt, NULL);
	
	Command::_currentCommand.prompt();
	yyparse();
}

