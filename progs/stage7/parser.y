
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
	int sptop=4096,bind;
	struct Typetable* typeptr,*typeptr2;
	char* typename,*classname,*typename2;
	struct Lsymbol* lptr;
	struct Classtable* Cptr;
	
%}
%union{
	struct tnode* p;
	int n;
	char* c;
	struct Paramstruct* paramptr;
	struct Typetable* type;
	struct Fieldlist* fieldlist;
}
%token NUM PLUS MINUS MUL DIV ID begin END READ WRITE EOL IF then ELSE endif WHILE DO endwhile GT LT LE GE NE EQ ASSIGN BREAK CONTINUE INT STR DECL ENDDECL STRING MOD RET MAIN AND OR TYPEDECL ENDTYPE INIT ALLOC FREE CLASS ENDCLASS EXTENDS SELF NEW
%type<p> expr Slist Stmt Breakstmt Continuestmt InputStmt OutputStmt AsgStmt Ifstmt Whilestmt Fdef Body MainBlock Retstmt ArgList Fieldd
%type<type> Type
%type<fieldlist> Field FieldList
%type<paramptr> ParamList Param IdList ParamList2
%nonassoc GT LT LE GE EQ NE
%left AND OR
%left PLUS MINUS
%left MUL DIV MOD

%%

Program : TypeBlock ClassDefBlock GdeclBlock FdefBlock MainBlock	{return 0;}
				|TypeBlock ClassDefBlock GdeclBlock MainBlock	{return 0;}
				|TypeBlock ClassDefBlock GdeclBlock FdefBlock {return 0;}
				|TypeBlock ClassDefBlock MainBlock	{return 0;}
				|ClassDefBlock GdeclBlock FdefBlock MainBlock	{return 0;}
				|ClassDefBlock GdeclBlock MainBlock	{return 0;}
				|ClassDefBlock GdeclBlock FdefBlock {return 0;}
				|ClassDefBlock MainBlock	{return 0;}
				;



ClassDefBlock : CLASS ClassDefList ENDCLASS
                |
	;
ClassDefList : ClassDefList ClassDef
               | ClassDef
	;
ClassDef      : Cname '{'DECL Fieldlists MethodDecl ENDDECL MethodDefns '}'
	;
Cname         : ID       	{Cptr = Cinstall($<c>1);classname=$<c>1;}         
              | ID EXTENDS ID	{//Cptr = Cinstall($1->Name,$3->Name);
              }
	;
Fieldlists : Fieldlists Fld 	{}
	| Fld			{}
	|			{}
	;     
Fld         : ID ID EOL		{ClassFinstall($<c>1,$<c>2);}
	;
MethodDecl : MethodDecl MDecl 	{Lsymbolroot=NULL;reset_fnargumentsbinding();}
	   | MDecl			{}
	   | 				{}
	;
MDecl: ID ID '(' ParamList ')' EOL 		{ClassMinstall(typelookuponly($<c>1),$<c>2,$4);} 
	;
MethodDefns : MethodDefns Fdef
            | Fdef
;






TypeBlock: TYPEDECL TypeEntryList ENDTYPE	{printTypeTable();}
	;

TypeEntryList: TypeEntryList TypeEntry
	|TypeEntry
	;
	
TypeEntry : ID '{' FieldList '}'	{typeinstallwithfields($<c>1,8,$3);}
	;

FieldList : FieldList Field	{$$=fieldappend($1,$2);}
	| Field	{$1->fieldIndex=0; $$=$1;}
	;
	
Field: Type ID EOL	{$$=fieldinstall($<c>2,$<type>1);}
	;

GdeclBlock : DECL GdeclList ENDDECL {sptop=getSP();printGsymbolTable(); Lsymbolroot=NULL;reset_fnargumentsbinding();}
	| DECL ENDDECL		{}
	;

GdeclList : GdeclList GDecl 
	| GDecl;
GDecl : ID GidList EOL	{updateTypeToGsymbol($<c>1);} //update the type to all elts who have type as NULL 
	;

GidList : GidList ',' Gid 
	| Gid;

Gid : ID 			{Ginstall($<c>1,NULL,1,-1,NULL,-1);}
	| ID'['NUM']' 		{Ginstall($<c>1,NULL,$<n>3,-1,NULL,-1);}
	| ID'('ParamList')' 	{Ginstall($<c>1,NULL,-1,-1,$<paramptr>3,-1);}
	;



FdefBlock : FdefBlock Fdef 
	| Fdef
	;

Fdef : Type ID '(' ParamList2 ')' '{' LdeclBlock Body '}'	{//if($<type>1!=$<p>8->type){printf("invalid fn ret type");exit(0);}
								 //if(Glookup($<c>2)==NULL){printf("fn not declared globally\n");exit(0);}
								 //functypecheck($4,Glookup($<c>2));
								 $$=$8;
								 $$->varname=$<c>2;
								 Lprint();
								 printf("%s\n",$$->varname);
								 codeGen(targetFile,$$);
								 printf("%s\n",$$->varname);
								 Lsymbolroot=NULL;reset_fnargumentsbinding();
								 } 
	;

/*param can be empty*/
ParamList2: ParamList			{Linstall("self",NULL);}
	;
ParamList : ParamList ',' Param 	{$<paramptr>$=addParam($<paramptr>1,$<paramptr>3);}
	| Param			{$<paramptr>$=$<paramptr>1;}
	|				{$<paramptr>$=NULL;}
	;

Param : Type ID	{$$=createParam($<c>2,$1);Linstall($<c>2,$1);}	//in global fn decl and fn defn
	;

Type : ID	{$$= typelookup($<c>1);}
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

IdList : IdList ',' ID		{$<paramptr>$=addParam($<paramptr>1,createParam($<c>3,NULL));}
	| ID			{$$=createParam($<c>1,NULL);}
	;
	


MainBlock : ID MAIN '(' ')' '{' LdeclBlock Body '}'		//where id is int
                                {$$=$7;
                                 $$->right->val=tMAINLabel;
                                 Lprint();
                                 codeGen(targetFile,$$);
                                 Lsymbolroot=NULL;reset_fnargumentsbinding();
                                }
          ;
          
          
          
Body      : begin Slist Retstmt END	{$$ = createTree(-1,$3->type,NULL,tFBODY,NULL,NULL,$2,$3,NULL,Clookup(classname));}     
          ;
          
          
Retstmt : RET expr EOL		{$$ = createTree(-1,$2->type,NULL,tRET,NULL,NULL,$2,NULL,NULL,NULL);}
	| RET EOL		{$$ = createTree(-1,typelookup("void"),NULL,tRET,NULL,NULL,NULL,NULL,NULL,NULL);}	
	;          
          

Slist : Slist Stmt		{$$=createTree(-1,NULL,NULL,tCONNECT,NULL,NULL,$1,$2,NULL,NULL);}
	| Stmt			{$$=$1;}
	|			{$$=NULL;}	
	;

Stmt : InputStmt 		{$$=$1;}
	| OutputStmt 		{$$=$1;}
	| AsgStmt 		{$$=$1;}
	| Ifstmt		{$$=$1;}
	| Whilestmt		{$$=$1;}
	| Breakstmt		{$$=$1;}
	| Continuestmt		{$$=$1;}
	;

Breakstmt : BREAK EOL			{$$=createTree(-1,NULL,NULL,tBREAK,NULL,NULL,NULL,NULL,NULL,NULL);}
	;

Continuestmt : CONTINUE EOL		{$$=createTree(-1,NULL,NULL,tCONTINUE,NULL,NULL,NULL,NULL,NULL,NULL);}
	;
InputStmt : READ '('expr ')' EOL	{$$=createTree(-1,NULL,NULL,tREAD,NULL,NULL,$3,NULL,NULL,NULL);}  
	;

OutputStmt : WRITE '(' expr ')' EOL	{$$=createTree(-1,NULL,NULL,tWRITE,NULL,NULL,$3,NULL,NULL,NULL);} 
	;

AsgStmt : expr ASSIGN expr EOL 	{$$ = createTree(-1,NULL,NULL,tASSIGN,NULL,NULL,$1,$3,NULL,NULL);} 
	;
Ifstmt : IF '(' expr ')' then Slist ELSE Slist endif EOL	{$$=createTree(-1,NULL,NULL,tIF,NULL,NULL,$3,$6,$8,NULL);}
	| IF '(' expr ')' then Slist endif EOL		{$$=createTree(-1,NULL,NULL,tIF,NULL,NULL,$3,$6,NULL,NULL);}
	;
Whilestmt : WHILE '(' expr ')' DO Slist endwhile EOL		{$$=createTree(-1,NULL,NULL,tWHILE,NULL,NULL,$3,$6,NULL,NULL);}
	;
expr : expr PLUS expr		{$$ = createTree(-1,typelookup("int"),NULL,tADD,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr MINUS expr  	{$$ = createTree(-1,typelookup("int"),NULL,tSUB,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr MUL expr	{$$ = createTree(-1,typelookup("int"),NULL,tMUL,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr MOD expr	{$$ = createTree(-1,typelookup("int"),NULL,tMOD,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr DIV expr	{$$ = createTree(-1,typelookup("int"),NULL,tDIV,NULL,NULL,$1,$3,NULL,NULL);}
	 | '(' expr ')'	{$$ = $2;}
	 | expr LT expr 		{$$ = createTree(-1,typelookup("bool"),NULL,tLT,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr GT expr 		{$$ = createTree(-1,typelookup("bool"),NULL,tGT,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr LE expr 		{$$ = createTree(-1,typelookup("bool"),NULL,tLE,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr GE expr 		{$$ = createTree(-1,typelookup("bool"),NULL,tGE,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr NE expr 		{$$ = createTree(-1,typelookup("bool"),NULL,tNE,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr EQ expr		{$$ = createTree(-1,typelookup("bool"),NULL,tEQ,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr AND expr		{$$ = createTree(-1,typelookup("bool"),NULL,tAND,NULL,NULL,$1,$3,NULL,NULL);}
	 | expr OR expr		{$$ = createTree(-1,typelookup("bool"),NULL,tOR,NULL,NULL,$1,$3,NULL,NULL);}
	 | NUM			{$$=createTree($<n>1,typelookup("int"),NULL,tNUM,NULL,NULL,NULL,NULL,NULL,NULL);}
	 | ID			{$$ = createTree(-1,typesearch($<c>1),$<c>1,tVAR,Llookup($<c>1),Glookup($<c>1),NULL,NULL,NULL,Clookup($<c>1));}
	 | STRING		{$$ = $<p>1;}	
	 | ID '[' expr ']'	{$$= createTree(-1,typesearch($<c>1),$<c>1,tARRAY,NULL,Glookup($<c>1),$3,NULL,NULL,NULL);}
	
	 | ID '('')' 		{$$ = createTree(-1,typesearch($<c>1),$<c>1,tFUNC,NULL,Glookup($<c>1),NULL,NULL,NULL,NULL);}
	 | ID '(' ArgList ')'	{$$ = createTree(-1,typesearch($<c>1),$<c>1,tFUNC,NULL,Glookup($<c>1),$3,NULL,NULL,NULL);}
	 | Fieldd		{$$=$1;}
	 | INIT'('')'		{$$ = createTree(-1,NULL,NULL,tINIT,NULL,NULL,NULL,NULL,NULL,NULL);}
	 | ALLOC '('')'	{$$ = createTree(-1,NULL,NULL,tALLOC,NULL,NULL,NULL,NULL,NULL,NULL);}
	 | NEW '(' ID ')'	{$$ = createTree(-1,NULL,NULL,tALLOC,NULL,NULL,NULL,NULL,NULL,NULL);}
	 | FREE '(' ID ')'	{$<p>3 = createTree(-1,typesearch($<c>3),$<c>3,tTYPEFIELD,Llookup($<c>3),Glookup($<c>3),NULL,NULL,NULL,NULL);
	 			$<p>$= createTree(-1,NULL,NULL,tFREE,NULL,NULL,$<p>3,NULL,NULL,NULL);}		
	 ;

Fieldd : Fieldd '.' ID {typename=$<c>3;
		$<p>3 = createTree(-1,typelookup($<p>1->varname),$<c>3,tFIELD,Llookup($<c>1),Glookup($<c>1),NULL,NULL,NULL,NULL);
		$<p>$ = createTree(-1,fieldtypelookup($<p>1->varname,typename),$<c>1,tDOT,Llookup($<c>1),Glookup($<c>1),$<p>1,$<p>3,NULL,NULL);}
	| ID '.' ID {if(Glookup($<c>1)!=NULL && Glookup($<c>1)->Ctype!=NULL){
			typename=$<c>1;
			$<p>1 = createTree(-1,NULL,$<c>1,tCLASSOBJ,NULL,Glookup($<c>1),NULL,NULL,NULL,NULL);
			$<p>3 = createTree(-1,NULL,$<c>3,tCLASSFIELD,NULL,Glookup(typename),NULL,NULL,NULL,NULL);
			$<p>$ = createTree(-1,NULL,typename,tCLASSDOT,NULL,Glookup(typename),$<p>1,$<p>3,NULL,NULL);
		}else{
			if(typesearch($<c>1)!=fieldtype($<c>1,$<c>3)){
				typename=fieldtype($<c>1,$<c>3)->name;
			}else{
				typename=typesearch($<c>1)->name;
			}
			typeptr=typesearch($<c>1);
			typeptr2=fieldtype($<c>1,$<c>3);
			typename=$<c>1;
			$<p>1 = createTree(-1,typeptr,$<c>1,tTYPEFIELD,Llookup($<c>1),Glookup($<c>1),NULL,NULL,NULL,NULL);
			$<p>3 = createTree(-1,typeptr,$<c>3,tFIELD,Llookup(typename),Glookup(typename),NULL,NULL,NULL,NULL);
			$<p>$ = createTree(-1,typeptr2,typename,tDOT,Llookup(typename),Glookup(typename),$<p>1,$<p>3,NULL,NULL);
	}}
	|ID '.' ID '(' ArgList ')'	{$<p>$=createTree(0,NULL,$<c>3,tMETHOD,NULL,Glookup($<c>1),$5,NULL,NULL,NULL);
		}
	| ID '.' ID '.' ID '(' ArgList ')'	{
		bind=getBindingForMethod2($<c>1,$<c>3);
		$<p>$=createTree(bind,NULL,$<c>3,tMETHOD,NULL,Glookup($<c>1),$7,NULL,NULL,Clookup(classname));
		}
	| SELF '.' ID '(' ArgList ')'	{$<p>$=createTree(0,NULL,$<c>3,tSELFMETHOD,NULL,NULL,$5,NULL,NULL,Clookup(classname));
		}
	| SELF '.' ID '.' ID '(' ArgList ')'	{$<p>3 = createTree(-1,NULL,$<c>3,tVAR,NULL,NULL,NULL,NULL,NULL,NULL);
		$<p>$=createTree(-1,NULL,$<c>5,tSELFMETHOD2,NULL,NULL,$7,$<p>3,NULL,Clookup(classname));}
	| SELF '.' ID '.' ID	{typename=$<c>3;typename2=$<c>5;
		$<p>1 = createTree(-1,NULL,NULL,tSELF,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
		$<p>3 = createTree(-1,NULL,$<c>3,tCLASSFIELD2,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
		$<p>5 = createTree(-1,findclassmemtype(classname,typename),typename2,tFIELD,Llookup($<c>1),Glookup($<c>1),NULL,NULL,NULL,NULL);
		$<p>$ = createTree(-1,NULL,NULL,tDOT,Llookup($<c>1),Glookup($<c>1),createTree(-1,NULL,classname,tCLASSDOT,NULL,NULL,$<p>1,$<p>3,NULL,Clookup(classname)),$<p>5,NULL,NULL);}
	| SELF '.' ID	{$<p>1 = createTree(-1,NULL,NULL,tSELF,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
			$<p>3 = createTree(-1,NULL,$<c>3,tCLASSFIELD2,NULL,NULL,NULL,NULL,NULL,Clookup(classname));
			$<p>$ = createTree(-1,NULL,classname,tCLASSDOT,NULL,NULL,$<p>1,$<p>3,NULL,Clookup(classname));
			}
	;

ArgList : ArgList ',' expr 	{$$=appendArgList($1,$3);}
	| expr			{$$=$1;}
	|			{$$=NULL;}
	;
	
%%

int yyerror(char const *s)
{
    printf("yyerror %s and %s",s,yytext);
}

int main(int argc, char*argv[]) {
	typeinstall("int");
	typeinstall("str");
	typeinstall("bool");
	typeinstall("void");
	typeinstall("NULL");
	typeinstallwithfields("int",1,NULL);
	typeinstallwithfields("str",1,NULL);
	typeinstallwithfields("bool",1,NULL);
	typeinstallwithfields("void",1,NULL);
	typeinstallwithfields("NULL",1,NULL);
	targetFile=fopen("targetFile.xsm","w");
	if(targetFile==NULL){
		printf("file error\n");
	}
	yyin=fopen(argv[1],"r");
	fprintf(targetFile,"%d\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n",0,"###",0,0,0,0,1,0);
	yyparse();
	fclose(targetFile);
	return 0;
}
