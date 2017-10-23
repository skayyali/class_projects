
/*
 * CS-252 Spring 2013
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%token	<string_val> WORD

%token 	NOTOKEN GREAT NEWLINE LESS PIPE AMP GREATGREAT GREATAMP GREATGREATAMP

%union	{
		char   *string_val;
	}

%{
//#define yylex yylex
#include <stdio.h>
#include "command.h"
#include <string.h>
#include <regex.h>
#include <sys/types.h>
#include <dirent.h>
void yyerror(const char * s);
int yylex();
void expandWildcardsIfNecessary(char*);
void expandWildcards(char *, char *);

%}

%%

goal:	
	commands
	;

commands: 
	command
	| commands command 
	;

command: simple_command
        ;

simple_command:	
	pipe_list iomodifier_list background NEWLINE {
		//printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE {
		Command::_currentCommand.clear();
		Command::_currentCommand.prompt();
	}
	| error NEWLINE { yyerrok; }
	;

pipe_list:
	pipe_list PIPE command_and_args
	| command_and_args

	;

command_and_args:
	command_word arg_list {
		Command::_currentCommand.
			insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;

arg_list:
	arg_list argument
	| /* can be empty */
	;

argument:
	WORD {
               //printf("   Yacc: insert argument \"%s\"\n", $1);
		//Change to expandWildcardIfNecessary($1)
	      // Command::_currentSimpleCommand->insertArgument( $1 );
	      expandWildcardsIfNecessary($1);
	}
	;

command_word:
	WORD {
               //printf("   Yacc: insert command \"%s\"\n", $1);
	       
	       Command::_currentSimpleCommand = new SimpleCommand();
	       Command::_currentSimpleCommand->insertArgument( $1 );
	}
	
	;

iomodifier_list:
	iomodifier_list iomodifier_opt
	|
	;
/*

	Increment counters for input, output, and error redirection

*/
iomodifier_opt:
	GREAT WORD {
		//printf("   Yacc: insert output \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._outFileCounter++;
	}
	| LESS WORD {
		//printf("   Yacc: input from \"%s\"\n", $2);
		Command::_currentCommand._inputFile = $2;
		Command::_currentCommand._inFileCounter++;
	}
	| GREATGREAT WORD {
		//printf("   Yacc: append output\"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._append = 1;
		Command::_currentCommand._outFileCounter++;
	}
	| GREATAMP WORD {
		//printf("   Yacc: output Error and Stdout to file \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._errFile = $2;
		Command::_currentCommand._outFileCounter++;
		Command::_currentCommand._errFileCounter++;
	}
	| GREATGREATAMP WORD {
		//printf("   Yacc: append output Error and Stdout to file \"%s\"\n", $2);
		Command::_currentCommand._outFile = $2;
		Command::_currentCommand._errFile = $2;
		Command::_currentCommand._append = 1;
		Command::_currentCommand._outFileCounter++;
		Command::_currentCommand._errFileCounter++;
	}
	;
background:
	AMP {
		Command::_currentCommand._background = 1;
	}
	|
	;
%%

/*

	To Do: Expandwildcardifnecessary()
		and expandwildcard()

*/
void expandWildcardsIfNecessary(char* arg)
{
	//it is not a wildcard
	if(strchr(arg, '*') == NULL && strchr(arg, '?') == NULL) {
		Command::_currentSimpleCommand->insertArgument(arg);
		//fprintf(stdout, "%s\n", arg);
		return;
	}
	else{
		char * tab = (char*)"";
		expandWildcards(tab , arg);
	}
}

void expandWildcards(char* prefix, char* suffix){
	// add ./ if there is no / to start in current directory
	// The first thing here:
	// 	Identify the first slash
	// 		strchr() -> returns a pointer to the location of the first slash
	// Second
	//	Move the first slash into prefix
	//	Move everything in suffix up to the next slash
	//		into a variable
	//	Check for wildcards in this variable
	//	If not, 		
	//		Append the string in the variable to prefix
	//		Recrusively call expandWildcards(prefix, suffix);
	//	Else,
	//		perform wildcard expansion (see slide 1)
	//		You're going to opendir(prefix)
	//		While through every directory/file in the opened directory
	//		If it matches with regexec,
	//			*SUBDIR EXPANSION* check for wildcards, if exist: call expandWildcards(prefix. suffix)
	//			If no wildcards, add to arguments. Keep in mind, you'll have to sort this list later.

	//printf("suff:%s\n", suffix);
	//printf("pref:%s\n", prefix);

	if(*suffix == '\0'){
		Command::_currentSimpleCommand->insertSortedArgument(strdup(prefix));
		return;
	}
	if(*suffix== '/') {
		char * nPrefix = (char*)malloc((strlen(prefix)+1)*sizeof(char));		
		strcpy(nPrefix, prefix);
		strcat(nPrefix, "/");
		prefix = nPrefix;
		char * suff = (char*)malloc((strlen(suffix)-1)*sizeof(char));
		strncpy(suff, suffix+1, (strlen(suffix))*sizeof(char));
		suffix=suff;
		
	}
	else if(*suffix!='/'){
		char * nPrefix = (char*)malloc((strlen(prefix)+2)*sizeof(char));
		strcpy(nPrefix, "./");
		strcat(nPrefix, prefix);
		prefix = nPrefix;
	}
	else{
		//char * nPrefix = (char*)malloc((strlen(prefix)+2)*sizeof(char));
		//strcpy(nPrefix, prefix);
		//strcat(nPrefix, "./");
		//prefix = nPrefix;
		//printf("nPref:%s\n", nPrefix);
	}


	char * slash = strchr(suffix, '/');
	int lengthOfComp;
	if(slash == NULL) {
		lengthOfComp = strlen(suffix);
		
	}
	else {
		lengthOfComp = slash-suffix;
	}

	char * comp = (char*)malloc((lengthOfComp+1)*sizeof(char));
	strncpy(comp, suffix, lengthOfComp);
	comp[lengthOfComp] = '\0';

	char * suff = (char*)malloc((abs(strlen(suffix)-lengthOfComp)+1)*sizeof(char));
	/*for(int x = 0; x < abs(strlen(suffix)-lengthOfComp+1); x++)
		suff[x] = '\0';*/
	strcpy(suff, suffix+lengthOfComp);
	suffix = suff;
	
	if(strchr(comp, '*') == NULL && strchr(comp, '?') == NULL){
		char * nPrefix = (char*)malloc((strlen(prefix)+strlen(comp))*sizeof(char));
		strcpy(nPrefix, prefix);
		strcat(nPrefix, comp);
		prefix = nPrefix;
		prefix[strlen(prefix)+strlen(comp)] = '\0';
		expandWildcards(prefix, suffix);
		free(comp);
		return;
	}

	
	char * reg = (char*)malloc(2*strlen(suffix)+10);
	char * a = comp;
	char * r = reg;
	*r = '^'; r++; // match beginning of the line (add ^)
	while (*a) {
	    if (*a == '*') { *r='.'; r++; *r='*'; r++; }
	    else if (*a == '?') { *r='.'; r++;}
	    else if (*a == '.') { *r='\\'; r++; *r='.'; r++;}
	    else { *r=*a; r++;}
	    a++;
	}
	*r='$'; r++; *r=0; // match end of line and add null char (add $)

	regex_t re;	
	int result = regcomp( &re, reg,  REG_EXTENDED|REG_NOSUB);
	if( result != 0 ) {
		fprintf(stdout, "Bad regular expresion\n");
		exit( -1 );
	}
	//fprintf(stdout, "%s\n", r);

	DIR * dir = opendir(prefix);
	if (dir == NULL) {
		if (*suffix == '\0' && *comp == '\0') {
			Command::_currentSimpleCommand->insertSortedArgument(strdup(prefix));
		}
		return;
	}

	regmatch_t match;
	struct dirent * ent; 
	while ( (ent = readdir(dir))!= NULL) {
		// Check if name matches
		if (regexec( &re,ent->d_name, 0, 0, 0 ) == 0 ) {
			if((comp[0] == '.' && ent->d_name[0] == '.') || (comp[0] != '.' && ent->d_name[0] != '.'))
			{

				// Add argument
				char * nPrefix = (char*)malloc((strlen(prefix)+strlen(ent->d_name))*sizeof(char));
				strcpy(nPrefix, prefix);
				strcat(nPrefix, ent->d_name);

				expandWildcards(nPrefix, suffix);
				//Command::_currentSimpleCommand->insertSortedArgument(strdup(ent->d_name));
			}
		}
	}

	closedir(dir);
	regfree(&re);
}

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}


#if 0
main()
{
	yyparse();
}
#endif
