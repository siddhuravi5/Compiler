
%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "exprtree.h"
	#include "exprtree.c"
	FILE* targetFile;
	int yylex(void);
	extern FILE *yyin;
	extern char* yytext;
	int sptop=4096;
	
%}
%union{
	struct tnode* p;
}
%token NUM PLUS MINUS MUL DIV ID begin END READ WRITE EOL IF then ELSE endif WHILE DO endwhile GT LT LE GE NE EQ ASSIGN BREAK CONTINUE INT STR DECL ENDDECL STRING MOD
%type<p> expr Slist Stmt Breakstmt Continuestmt InputStmt OutputStmt AsgStmt Ifstmt Whilestmt ID VarList Type STRING NUM
%nonassoc GT LT LE GE EQ NE
%left PLUS MINUS
%left MUL DIV MOD

%%
Program : begin Declarations Slist END EOL	{ sptop=getSP();
fprintf(targetFile,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nMOV SP, %d\n",0,2056,0,0,0,0,1,0,sptop);
				codeGen(targetFile,$3);
				printExit(targetFile);
				return 0;				
				}
	| begin END EOL	{printf("Empty program\n;");return 0;}
	;

Slist : Slist Stmt		{$$=createTree(-1,-1,NULL,tCONNECT,NULL,$1,$2,NULL);}
	| Stmt			{$$=$1;} 	
	;

Stmt : InputStmt 		{$$=$1;}
	| OutputStmt 		{$$=$1;}
	| AsgStmt 		{$$=$1;}
	| Ifstmt		{$$=$1;}
	| Whilestmt		{$$=$1;}
	| Breakstmt		{$$=$1;}
	| Continuestmt		{$$=$1;}
	;

Declarations : DECL DeclList ENDDECL EOL	{printSymbolTable();} 
	| DECL ENDDECL	EOL		{printSymbolTable();}
	;
DeclList : DeclList Decl 		{}
	| Decl				{}
	;
Decl : Type VarList EOL	{symboltype($1,$2);}
	;
Type : INT 			{$$=createTree(-1,tINT,NULL,-1,NULL,NULL,NULL,NULL);}
	| STR			{$$=createTree(-1,tSTR,NULL,-1,NULL,NULL,NULL,NULL);}
	;
VarList : VarList ',' ID 	{$$=createTree(-1,-1,NULL,-1,NULL,$1,$3,NULL);}
	| ID			{$$=$1;}
	|VarList ',' ID '[' NUM ']' 	{$$=createTree(-1,-1,NULL,-1,NULL,$1,$3,NULL);}
	| ID '[' NUM ']'		{$$=$1;}
	;

Breakstmt : BREAK EOL			{$$=createTree(-1,-1,NULL,tBREAK,NULL,NULL,NULL,NULL);}
	;

Continuestmt : CONTINUE EOL		{$$=createTree(-1,-1,NULL,tCONTINUE,NULL,NULL,NULL,NULL);}
	;
InputStmt : READ '('expr ')' EOL	{$$=createTree(-1,-1,NULL,tREAD,NULL,$3,NULL,NULL);}  
	;

OutputStmt : WRITE '(' expr ')' EOL	{$$=createTree(-1,-1,NULL,tWRITE,NULL,$3,NULL,NULL);} 
	;

AsgStmt : expr ASSIGN expr EOL {$$ = createTree(-1,-1,NULL,tASSIGN,NULL,$1,$3,NULL);} 
	;
Ifstmt : IF '(' expr ')' then Slist ELSE Slist endif EOL	{$$=createTree(-1,-1,NULL,tIF,NULL,$3,$6,$8);}
	| IF '(' expr ')' then Slist endif EOL		{$$=createTree(-1,-1,NULL,tIF,NULL,$3,$6,NULL);}
	;
Whilestmt : WHILE '(' expr ')' DO Slist endwhile EOL		{$$=createTree(-1,-1,NULL,tWHILE,NULL,$3,$6,NULL);}
	;
expr : expr PLUS expr		{$$ = createTree(-1,-1,NULL,tADD,NULL,$1,$3,NULL);}
	 | expr MINUS expr  	{$$ = createTree(-1,-1,NULL,tSUB,NULL,$1,$3,NULL);}
	 | expr MUL expr	{$$ = createTree(-1,-1,NULL,tMUL,NULL,$1,$3,NULL);}
	 | expr MOD expr	{$$ = createTree(-1,-1,NULL,tMOD,NULL,$1,$3,NULL);}
	 | expr DIV expr	{$$ = createTree(-1,-1,NULL,tDIV,NULL,$1,$3,NULL);}
	 | '(' expr ')'	{$$ = $2;}
	 | expr LT expr 		{$$ = createTree(-1,-1,NULL,tLT,NULL,$1,$3,NULL);}
	 | expr GT expr 		{$$ = createTree(-1,-1,NULL,tGT,NULL,$1,$3,NULL);}
	 | expr LE expr 		{$$ = createTree(-1,-1,NULL,tLE,NULL,$1,$3,NULL);}
	 | expr GE expr 		{$$ = createTree(-1,-1,NULL,tGE,NULL,$1,$3,NULL);}
	 | expr NE expr 		{$$ = createTree(-1,-1,NULL,tNE,NULL,$1,$3,NULL);}
	 | expr EQ expr		{$$ = createTree(-1,-1,NULL,tEQ,NULL,$1,$3,NULL);}
	 | NUM			{$$=$1;}
	 | ID			{$$ = $1;}
	 | STRING		{$$ = $1;}	
	 | ID '[' expr ']'	{$$= createTree(-1,$1->Gentry->type,$1->Gentry->name,tARRAY,$1->Gentry,$3,NULL,NULL);}
	 ;

%%

int yyerror(char const *s)
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
