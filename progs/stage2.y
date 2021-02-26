%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "exprtree.h"
	#include "exprtree.c"
	int yylex(void);
	extern FILE *yyin;
	struct tnode *root;
	FILE* targetFile;
	int reg=0;
%}

%type <struct tnode *> expr NUM program ID Slist Stmt InputStmt OutputStmt AssgStmt
%token NUM PLUS MINUS MUL DIV END ID BEGIN END READ WRITE EOL EQ
%left PLUS MINUS
%left MUL DIV

%%
Program : BEGIN Slist END EOL	{root=$2;
				fprintf(fout,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nMOV SP, 4121\n",0,2056,0,0,0,0,1,0);
				codeGen(targetFile,$2);
				printExit(targetFile);				
				}
	| BEGIN END EOL	{printf("Empty program\n;");return;}
	;

Slist : Slist Stmt		{$$=createTree(NULL,NULL,NULL,tCONNECT,$1,$2);}
	| Stmt			{$$=$1;} 	
	;

Stmt : InputStmt 		{$$=$1;}
	| OutputStmt 		{$$=$1;}
	| AsgStmt 		{$$=$1;}
	;

InputStmt : READ '(' ID ')' EOL	{$$=createTree(NULL,NULL,NULL,tREAD,$3,NULL)}  
	;

OutputStmt : WRITE '(' E ')' EOL	{$$=createTree(NULL,NULL,NULL,tWRITE,$3,NULL)} 
	;

AsgStmt : ID EQ E EOL {$$ = createTree(-1,-1,NULL,tASSIGN,$1,$3);} 
	;

expr : expr PLUS expr		{$$ = createTree(NULL,NULL,NULL,tADD,$1,$3);}
	 | expr MINUS expr  	{$$ = createTree(NULL,NULL,NULL,tSUB,$1,$3);}
	 | expr MUL expr	{$$ = createTree(NULL,NULL,NULL,tMUL,$1,$3);}
	 | expr DIV expr	{$$ = createTree(NULL,NULL,NULL,tDIV,$1,$3);}
	 | '(' expr ')'	{$$ = $2;}
	 | NUM			{$$ = $1;}
	 | ID			{$$ = $1;}
	 ;

%%

yyerror(char const *s)
{
    printf("yyerror %s",s);
}


int main(int argc, char*argv[]) {
	targetFile=fopen("targetFile.xsm","w");

	yyin=fopen(argv[1],"r");
	yyparse();
	return 0;
}
