%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "y.tab.h"
	#include "exprtree.h"
	int number;

%}

%%

begin {return begin;}
end {return END;}
read {return READ;}
write {return WRITE;}
[0-9]+	{return NUM;}
[a-z] { return ID;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
"="	{return EQ;}
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
