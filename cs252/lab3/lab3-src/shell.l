
/*
 *
 * CS-252 Fall 2013
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include "y.tab.h"
#include "command.h"
#include <sys/types.h>
#include <sys/wait.h>
extern int main();
static void yyunput (int c,char *buf_ptr  );
void escapeCharacters();
void myunputc(int c) {
    unput(c);
}

%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}

"<" 	{
		return LESS;
	}

"|"	{
		return PIPE;
	}
"&"     {
		return AMP;
	}
">>"	{
		return GREATGREAT;
	}
">&"	{	
		return GREATAMP;
	}
">>&"	{
		return GREATGREATAMP;
	}
`[^\n`]*`	{
		char* comm = strdup(yytext);
		int len = strlen(comm);
		comm[len-1]= '\0';
		yylval.string_val = comm+1;

		int inputPipe[2]; // pipe in
		int outputPipe[2]; // pipe out
		pipe(inputPipe); 
		pipe(outputPipe);
		int in = dup(0); // save
		int out = dup(1); //save 

		
		

		int pid;
		pid = fork();
		if(pid == -1){
			perror("shell:fork\n");
			exit(2);
		}
		if(pid == 0){
			//child
			dup2(inputPipe[0],0);
			dup2(outputPipe[1],1);
			close(inputPipe[0]);
			close(outputPipe[0]);
			close(inputPipe[1]);
			close(outputPipe[1]);

			int q = main();

		}
		
		dup2(in, 0);
		dup2(out, 1);
		close(in);
		close(out);
		write(inputPipe[1],yylval.string_val, strlen(yylval.string_val));
		write(inputPipe[1],"\nexit\n", strlen("\nexit\n"));
		waitpid(pid, NULL, 0);
		close(inputPipe[1]);
		close(outputPipe[1]);
		
		char * arg = (char*)malloc(5000);
		int result = read(outputPipe[0], arg, 5000);
		
		char * temp = strtok(arg, " \n\t");
		while(temp != NULL){
			Command::_currentSimpleCommand->insertArgument(strdup(temp));
			temp = strtok(NULL, " \n\t");
		}
		
		close(outputPipe[0]);
		free(arg);
		free(temp);

}


[^ \|\>>\&\>&\>>&\<\>\t\n][^ \|\>>\&\>&\>>&\<\>\t\n]*  {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}


\"[^\n\"]*\"	{
		char* quotes = yytext;
		quotes++;
		yytext = quotes;
		yytext[strlen(yytext)-1] = '\0';
		yylval.string_val = strdup(yytext);
		return WORD;
	}
[^ \t\n]*(\\[^\s])[^ \t\n]*	{
		escapeCharacters();
		yylval.string_val = strdup(yytext);
		return WORD;
	}

	
		
%%

void escapeCharacters()
{
	char * text = (char*)malloc(strlen(yytext)+1);
	int escape = 0;
	int a = 0;
	
	for(int i = 0; i < strlen(yytext); i++)
	{
		if(yytext[i] == '\\' && escape == 0)
		{
			escape = 1;
		}
		else if (escape)
		{
			text[a] = yytext[i];
			a++;
			escape = 0;
		}
		else
		{
			text[a] = yytext[i];
			a++;
		}
	}
	text[a] = '\0';
	strcpy(yytext, text);
	free(text);
}
