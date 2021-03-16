%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "exprtree.h"
	int addr=2054;	//correct address -2
	//int LT[20];
	FILE* fp1;
	FILE* fp2;
%}

%%

###		{int number=tMAINLabel;
		int i=0;
		fgetc(fp1);
		fscanf(fp1,"%d",&i);
		fgetc(fp1);
		while(i!=number){
			fscanf(fp1,"%d",&i);
			fgetc(fp1);
		}
		int address	;
		fscanf(fp1,"%d",&address);
		rewind(fp1);
		fprintf(fp2,"%d",address);}
L[0-9]+:[\n]	{}
L[0-9]+	{yytext+=1;
		char num[10];
		int i=0;
		int j=yyleng-1;
		while(i<j){
			num[i]=yytext[0];
			i++;
			yytext+=1;
		}
		num[i]='\0';
		int number=atoi(num);
		i=0;
		fgetc(fp1);
		fscanf(fp1,"%d",&i);
		fgetc(fp1);
		while(i!=number){
			fscanf(fp1,"%d",&i);
			fgetc(fp1);
		}
		int address	;
		fscanf(fp1,"%d",&address);
		rewind(fp1);
		fprintf(fp2,"%d",address);}

[\n]	{fprintf(fp2,"\n");}
.	{fprintf(fp2,"%c",yytext[0]);}


%%

int yywrap(void) {
	return 1;
}

int main(int argc, char*argv[]){
	fp1=fopen("data.txt","r");
	fp2=fopen("targetT.xsm","w");
	yyin=fopen(argv[1],"r");
	//printf("check1\n");
	yylex();
	return 1;
}
