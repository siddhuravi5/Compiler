
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
	int n;
	char* c;
	struct Paramstruct* paramptr;
}
%token NUM PLUS MINUS MUL DIV ID begin END READ WRITE EOL IF then ELSE endif WHILE DO endwhile GT LT LE GE NE EQ ASSIGN BREAK CONTINUE INT STR DECL ENDDECL STRING MOD RET MAIN AND OR
%type<p> expr Slist Stmt Breakstmt Continuestmt InputStmt OutputStmt AsgStmt Ifstmt Whilestmt Fdef Body MainBlock Retstmt ArgList
%type<n> Type
%type<paramptr> Param IdList
%nonassoc GT LT LE GE EQ NE
%left AND OR
%left PLUS MINUS
%left MUL DIV MOD

%%

Program : GdeclBlock FdefBlock MainBlock	{return 0;}
	|GdeclBlock MainBlock	{return 0;}
	|GdeclBlock FdefBlock {return 0;}
	|MainBlock	{return 0;}
	;


GdeclBlock : DECL GdeclList ENDDECL {sptop=getSP();
			fprintf(targetFile,"%d\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n",0,"###",0,0,0,0,1,0);printGsymbolTable(); Lsymbolroot=NULL;reset_fnargumentsbinding();}
	| DECL ENDDECL{sptop=getSP();
			fprintf(targetFile,"%d\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n",0,"###",0,0,0,0,1,0);}
	;

GdeclList : GdeclList GDecl 
	| GDecl;
GDecl : Type GidList EOL	{updateTypeToGsymbol($1);} //update the type to all elts who have type as NULL 
	;

GidList : GidList ',' Gid 
	| Gid;

Gid : ID 			{Ginstall($<c>1,-1,1,-1,NULL,-1);}
	| ID'['NUM']' 		{Ginstall($<c>1,-1,$<n>3,-1,NULL,-1);}
	| ID'('ParamList')' 	{Ginstall($<c>1,-1,-1,-1,$<paramptr>3,-1);}
	;



FdefBlock : FdefBlock Fdef 
	| Fdef
	;

Fdef : Type ID '(' ParamList ')' '{' LdeclBlock Body '}'	{//if(strcmp($1->name,$8->name)!=0){printf("invalid fn ret type");exit(0);}
								 //functypecheck($4,Glookup($<c>2)););
								 $$=$8;
								 $$->varname=$<c>2;
								 Lprint();
								 codeGen(targetFile,$$);
								  Lsymbolroot=NULL;reset_fnargumentsbinding();
								 } 
	;

/*param can be empty*/
ParamList : ParamList ',' Param 	{$<paramptr>$=addParam($<paramptr>1,$<paramptr>3);}
	| Param			{$<paramptr>$=$<paramptr>1;}
	|				{$<paramptr>$=NULL;}
	;

Param : Type ID	{$$=createParam($<c>2,$1);Linstall($<c>2,$1);}	//in global fn decl and fn defn
	;
	
Type : INT 	{$$=tINT;}
	| STR 	{$$=tSTR;}
	;





LdeclBlock : DECL LDecList ENDDECL 
	| DECL ENDDECL
	|
	;

LDecList : LDecList LDecl 
	| LDecl
	;
LDecl : Type IdList EOL 	{Linstallbylistwithtype($<paramptr>2,$1);}
	;

IdList : IdList ',' ID		{$<paramptr>$=addParam($<paramptr>1,createParam($<c>3,-1));}
	| ID			{$$=createParam($<c>1,-1);printf("p1\n");}
	;
	


MainBlock : INT MAIN '(' ')' '{' LdeclBlock Body '}'		//where id is int
                                {$$=$7;
                                 $$->right->val=tMAINLabel;
                                 Lprint();
                                 codeGen(targetFile,$$);
                                 Lsymbolroot=NULL;reset_fnargumentsbinding();
                                }
          ;
          
          
          
Body      : begin Slist Retstmt END	{$$ = createTree(-1,$3->type,NULL,tFBODY,NULL,NULL,$2,$3,NULL);}     
          ;
          
          
Retstmt : RET expr EOL		{$$ = createTree(-1,$2->type,NULL,tRET,NULL,NULL,$2,NULL,NULL);}
	| RET EOL		{$$ = createTree(-1,-1,NULL,tRET,NULL,NULL,NULL,NULL,NULL);}	
	;          
          

Slist : Slist Stmt		{$$=createTree(-1,-1,NULL,tCONNECT,NULL,NULL,$1,$2,NULL);}
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

Breakstmt : BREAK EOL			{$$=createTree(-1,-1,NULL,tBREAK,NULL,NULL,NULL,NULL,NULL);}
	;

Continuestmt : CONTINUE EOL		{$$=createTree(-1,-1,NULL,tCONTINUE,NULL,NULL,NULL,NULL,NULL);}
	;
InputStmt : READ '('expr ')' EOL	{$$=createTree(-1,-1,NULL,tREAD,NULL,NULL,$3,NULL,NULL);}  
	;

OutputStmt : WRITE '(' expr ')' EOL	{$$=createTree(-1,-1,NULL,tWRITE,NULL,NULL,$3,NULL,NULL);} 
	;

AsgStmt : expr ASSIGN expr EOL {$$ = createTree(-1,-1,NULL,tASSIGN,NULL,NULL,$1,$3,NULL);} 
	;
Ifstmt : IF '(' expr ')' then Slist ELSE Slist endif EOL	{$$=createTree(-1,-1,NULL,tIF,NULL,NULL,$3,$6,$8);}
	| IF '(' expr ')' then Slist endif EOL		{$$=createTree(-1,-1,NULL,tIF,NULL,NULL,$3,$6,NULL);}
	;
Whilestmt : WHILE '(' expr ')' DO Slist endwhile EOL		{$$=createTree(-1,-1,NULL,tWHILE,NULL,NULL,$3,$6,NULL);}
	;
expr : expr PLUS expr		{$$ = createTree(-1,-1,NULL,tADD,NULL,NULL,$1,$3,NULL);}
	 | expr MINUS expr  	{$$ = createTree(-1,-1,NULL,tSUB,NULL,NULL,$1,$3,NULL);}
	 | expr MUL expr	{$$ = createTree(-1,-1,NULL,tMUL,NULL,NULL,$1,$3,NULL);}
	 | expr MOD expr	{$$ = createTree(-1,-1,NULL,tMOD,NULL,NULL,$1,$3,NULL);}
	 | expr DIV expr	{$$ = createTree(-1,-1,NULL,tDIV,NULL,NULL,$1,$3,NULL);}
	 | '(' expr ')'	{$$ = $2;}
	 | expr LT expr 		{$$ = createTree(-1,-1,NULL,tLT,NULL,NULL,$1,$3,NULL);}
	 | expr GT expr 		{$$ = createTree(-1,-1,NULL,tGT,NULL,NULL,$1,$3,NULL);}
	 | expr LE expr 		{$$ = createTree(-1,-1,NULL,tLE,NULL,NULL,$1,$3,NULL);}
	 | expr GE expr 		{$$ = createTree(-1,-1,NULL,tGE,NULL,NULL,$1,$3,NULL);}
	 | expr NE expr 		{$$ = createTree(-1,-1,NULL,tNE,NULL,NULL,$1,$3,NULL);}
	 | expr EQ expr		{$$ = createTree(-1,-1,NULL,tEQ,NULL,NULL,$1,$3,NULL);}
	 | expr AND expr		{$$ = createTree(-1,-1,NULL,tAND,NULL,NULL,$1,$3,NULL);}
	 | expr OR expr		{$$ = createTree(-1,-1,NULL,tOR,NULL,NULL,$1,$3,NULL);}
	 | NUM			{$$=createTree($<n>1,-1,NULL,tNUM,NULL,NULL,NULL,NULL,NULL);}
	 | ID			{$$ = createTree(-1,-1,$<c>1,tVAR,Llookup($<c>1),Glookup($<c>1),NULL,NULL,NULL);}
	 | STRING		{$$ = $<p>1;}	
	 | ID '[' expr ']'	{$$= createTree(-1,-1,$<c>1,tARRAY,NULL,Glookup($<c>1),$3,NULL,NULL);}
	
	 | ID '('')' 		{$$ = createTree(-1,-1,$<c>1,tFUNC,NULL,Glookup($<c>1),NULL,NULL,NULL);}
	 | ID '(' ArgList ')'	{$$ = createTree(-1,-1,$<c>1,tFUNC,NULL,Glookup($<c>1),$3,NULL,NULL);}	
	 ;


ArgList : ArgList ',' expr 	{$$=appendArgList($1,$3);}
	| expr			{$$=$1;}
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
