%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "exprtree.h"
	#include "exprtree.c"
	#define YYSTYPE tnode*
	FILE* targetFile;
	int yylex(void);
	extern FILE *yyin;
	extern char* yytext;
	tnode *root;
	
%}

%token NUM PLUS MINUS MUL DIV ID begin END READ WRITE EOL EQ
%left PLUS MINUS
%left MUL DIV

%%
Program : begin Slist END EOL	{printf("finish\n");
				fprintf(targetFile,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nMOV SP, 4121\n",0,2056,0,0,0,0,1,0);
				codeGen(targetFile,$2);
				
				printf("%d",$2->nodetype);
				if($2->left==NULL){
					printf("left");
				}
				if($2->right==NULL){
					printf("right");
				}
				printf("%d",($2->left)->nodetype);
				//printf("%c",$2->left->varname[0]);
				printf("code over");
				printExit(targetFile);
				return 0;				
				}
	| begin END EOL	{printf("Empty program\n;");return 0;}
	;

Slist : Slist Stmt		{printf("SList\n");$$=createTree(-1,-1,NULL,tCONNECT,$1,$2);}
	| Stmt			{printf("stmt\n");$$=$1;} 	
	;

Stmt : InputStmt 		{$$=$1;}
	| OutputStmt 		{$$=$1;}
	| AsgStmt 		{$$=$1;}
	;

InputStmt : READ '(' expr ')' EOL	{$$=createTree(-1,-1,NULL,tREAD,$3,NULL);printf("input\n");}  
	;

OutputStmt : WRITE '(' expr ')' EOL	{$$=createTree(-1,-1,NULL,tWRITE,$3,NULL);printf("output\n");} 
	;

AsgStmt : expr EQ expr EOL {$$ = createTree(-1,-1,NULL,tASSIGN,$1,$3);printf("assg\n");} 
	;

expr : expr PLUS expr		{printf("add1\n");$$ = createTree(-1,-1,NULL,tADD,$1,$3);printf("add\n");}
	 | expr MINUS expr  	{$$ = createTree(-1,-1,NULL,tSUB,$1,$3);}
	 | expr MUL expr	{printf("mul1\n");$$ = createTree(-1,-1,NULL,tMUL,$1,$3);printf("mul2\n");}
	 | expr DIV expr	{$$ = createTree(-1,-1,NULL,tDIV,$1,$3);}
	 | '(' expr ')'	{$$ = $2;}
	 | NUM			{$$ = createTree(atoi(yytext),tINT,NULL,tNUM,NULL,NULL);printf("num\n");printf("%d",atoi(yytext));}
	 | ID			{$$ = createTree(-1,tINT,yytext,tVAR,NULL,NULL);printf("id:%c\n",yytext[0]);}
	 ;

%%

yyerror(char const *s)
{
    printf("yyerror %s and %s",s,yytext);
}


int main(int argc, char*argv[]) {
	targetFile=fopen("targetFile.xsm","w");
	if(targetFile==NULL){
		printf("file error\n");
	}
	yyin=fopen(argv[1],"r");
	yyparse();
	fclose(targetFile);
	return 0;
}
