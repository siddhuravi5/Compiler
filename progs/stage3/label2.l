%{
	#include <stdlib.h>
	#include <stdio.h>
	int addr=2054;	//correct address -2
	//int LT[20];
	FILE* fp1;
	FILE* fp2;
%}

%%

L[0-9]+:[\n]	{}
L[0-9]+	{//printf("check2\n");
		//printf("%s : %d\n",yytext,yyleng);
		yytext+=1;
		//printf("check2\n");
		char num[10];
		int i=0;
		int j=yyleng-1;
		while(i<j){
			num[i]=yytext[0];
			i++;
			yytext+=1;
		}
		//printf("check2\n");
		num[i]='\0';
		int number=atoi(num);
		i=0;
		//printf("%d",number);
		fgetc(fp1);
		fscanf(fp1,"%d",&i);
		fgetc(fp1);
		//printf("%d\n",i);
		while(i!=number){
			fscanf(fp1,"%d",&i);
			fgetc(fp1);
		}
		int address	;
		fscanf(fp1,"%d",&address);
		/*char numb[5];
		numb[0]=getc(fp1);
		numb[1]=getc(fp1);
		numb[2]=getc(fp1);
		numb[3]=getc(fp1);
		numb[4]='\0';*/
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
	fp2=fopen("target.xsm","w");
	yyin=fopen(argv[1],"r");
	//printf("check1\n");
	yylex();
	return 1;
}
