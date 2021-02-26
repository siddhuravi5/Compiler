%{
	#include <stdlib.h>
	#include <stdio.h>
	int addr=2054;	//correct address -2
	//int LT[20];
	FILE* fp;
%}

%%
(MOV|PUSH|POP|ADD|SUB|MUL|DIV|GT|LT|GE|LE|NE|EQ|INT|CALL|JZ|JNZ|JMP|BRKP|MOD)	{addr+=2;}

L[0-9]+:	{	yytext+=1;
		char num[3];
		int i=0;
		while(yytext[0]!=':'){
			num[i]=yytext[0];
			i++;
			yytext+=1;
		}
		num[i]='\0';		
		//printf("%s :: %d\n",num,atoi(num));
		fprintf(fp,"i%di%d",atoi(num),addr+2);}
		
[ \t]	{}	
[' '] {}
[\n]	{}
.	{}


%%

int yywrap(void) {
	return 1;
}

int main(int argc, char*argv[]){
	fp=fopen("data.txt","w");
	yyin=fopen(argv[1],"r");
	yylex();
	return 1;
}
