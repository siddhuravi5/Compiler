%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"
	#include "exprtree.h"
	int number;

%}

%%

"BEGIN" {return BEGIN;}
"END" {return END;}
"READ" {return READ;}
"WRITE" {return WRITE;}
[0-9]+	{number = atoi(yytext); yylval = createTree(number,NULL,NULL,NULL,NULL,NULL); return NUM;}
[a-z] {yylval = createTree(NULL,tINT,yytext,tVAR,NULL,NULL); return ID;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
"="	{return EQ;}
";" {return EOL;}
[ \t]	{}
[()]	{return *yytext;}
[\n]	{}
.	{yyerror("unknown character\n");exit(1);}


%%

int yywrap(void) {
	return 1;
}
