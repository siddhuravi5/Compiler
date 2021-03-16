%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "exprtree.h"
	int addr=2054;	//correct address -2
	//int LT[20];
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	int a,b,i;
%}

%%


L100:[\n]	{	
		fprintf(fp2,"L100:\n");
		fscanf(fp3,"%d",&a);
		//if(a==-10) return;
		while(a!=-10){
			fscanf(fp3,"%d",&b);
			int number=b;
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
			fprintf(fp2,"MOV R17,%d\n",a);
			fprintf(fp2,"MOV [R17],%d\n",address);
			printf("%d->%d\n",b,address);
			fscanf(fp3,"%d",&a);
		}	
	}

[\n]	{fprintf(fp2,"\n");}
.	{fprintf(fp2,"%c",yytext[0]);}


%%

int yywrap(void) {
	return 1;
}

int main(int argc, char*argv[]){
	fp1=fopen("data.txt","r");
	fp2=fopen("target.xsm","w");
	fp3=fopen("vFuncTable.txt","r");
	yyin=fopen(argv[1],"r");
	//printf("check1\n");
	yylex();
	return 1;
}
