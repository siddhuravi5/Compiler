%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"
	#include "exprtree.h"
	char* string;
%}

%%

begin	{printf("begin\n");return begin;}
end 	{printf("end\n");return END;}
class	{printf("class\n");return CLASS;}
endclass {printf("endclass\n");return ENDCLASS;}
type	{return TYPEDECL;}
extends {return EXTENDS;}
endtype {return ENDTYPE;}
self	{return SELF;}
new	{return NEW;}
decl	{printf("decl\n");return DECL;}
enddecl {printf("enddecl\n");return ENDDECL;}
break	{return BREAK;}
continue	{return CONTINUE;}
initialize	{return INIT;}
alloc	{return ALLOC;}
free	{return FREE;}
null	{yylval.n=99;return NUM;}
NULL	{yylval.n=99;return NUM;}
read 	{return READ;}
write 	{return WRITE;}
main	{return MAIN;}
AND	{return AND;}
"."	{return yytext[0];}
OR	{return OR;}
then 	{return then;}
else 	{return ELSE;}
return  {return RET;}
\".*\" {string=strdup(yytext);yylval.p=createTree(-1,typelookup("str"),string,tSTR,NULL,NULL,NULL,NULL,NULL,NULL);return STRING;}
endif	{return endif;}
if	{return IF;}
do	{return DO;}
endwhile {return endwhile;}
while	{return WHILE;}
[0-9]+	{yylval.n = atoi(yytext);
	return NUM;}
[A-Za-z][A-Za-z0-9]*[_]?[A-Za-z0-9]* {yylval.c=strdup(yytext);return ID;}
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
