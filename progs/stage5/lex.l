%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"
	#include "exprtree.h"
	char* string;
%}

%%

begin	{printf("begin\n");return begin;}
end 	{return END;}
decl	{printf("decl\n");return DECL;}
enddecl {return ENDDECL;}
int	{return INT;}
str	{return STR;}
break	{return BREAK;}
continue	{return CONTINUE;}
read 	{return READ;}
write 	{return WRITE;}
main	{return MAIN;}
AND	{return AND;}
OR	{return OR;}
then 	{return then;}
else 	{return ELSE;}
return  {return RET;}
\".*\" {string=strdup(yytext);yylval.p=createTree(-1,tSTR,string,-1,NULL,NULL,NULL,NULL,NULL);return STRING;}
endif	{return endif;}
if	{return IF;}
do	{return DO;}
endwhile {return endwhile;}
while	{return WHILE;}
[0-9]+	{yylval.n = atoi(yytext);
	return NUM;}
[A-Za-z][A-Za-z0-9]* {yylval.c=strdup(yytext);return ID;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"%"	{return MOD;}
"/"	{return DIV;}
"<="	{return LE;}
">="	{return GE;}
"<"	{return LT;}
">"	{return GT;}
"!="	{return NE;}
"=="	{return EQ;}
"="	{return ASSIGN;}
","	{return yytext[0];}
"["	{return yytext[0];}
"]"	{return yytext[0];}
"{"	{return yytext[0];}
"}"	{return yytext[0];}
";" {return EOL;}
[ \t]	{}
[' '] {}
[()]	{return *yytext;}
[\n]	{}
.	{}


%%

int yywrap(void) {
	return 1;
}
