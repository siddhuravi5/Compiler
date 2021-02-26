%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"
	#include "exprtree.h"
	int declbool=0;
	int number;
	char* string;
	//struct Gysmbol* groot;
%}

%%

begin	{return begin;}
end 	{return END;}
decl	{declbool=1;return DECL;}
enddecl	{declbool=0;return ENDDECL;}
int	{return INT;}
str	{return STR;}
break	{return BREAK;}
continue	{return CONTINUE;}
read 	{return READ;}
write 	{return WRITE;}
then 	{return then;}
else 	{return ELSE;}
\".*\" {string=strdup(yytext);yylval.p=createTree(-1,tSTR,string,-1,NULL,NULL,NULL,NULL);return STRING;}
endif	{return endif;}
if	{return IF;}
do	{return DO;}
endwhile {return endwhile;}
while	{return WHILE;}
[0-9]+	{if(declbool==1){
		number=atoi(yytext);
		//printf("installing\n");
		updateSizeToLatestId(number);
	}
	yylval.p = createTree(atoi(yytext),tINT,NULL,tNUM,NULL,NULL,NULL,NULL);
	return NUM;}
[A-Za-z][A-Za-z0-9]* {	if(declbool==1){
				string=strdup(yytext);
				//printf("installing\n");
				install(string, 0, 1);
			}
			//printf("looking\n");
			
			yylval.p=createTree(-1,tINT,yytext,tVAR,lookup(yytext),NULL,NULL,NULL);return ID;}
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
