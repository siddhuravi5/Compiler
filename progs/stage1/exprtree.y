%{
	#include <stdlib.h>
	#include <stdio.h>
	#include "exprtree1.h"
	#include "exprtree1.c"
	int yylex(void);
	extern FILE *yyin;
	struct tnode *root;
	FILE* targetFile;
	int reg=0;
%}

%union{
	struct tnode *no;
	
}
%type <no> expr NUM program END
%token NUM PLUS MINUS MUL DIV END
%left PLUS MINUS
%left MUL DIV

%%

program : expr END	{
				$$ = $2;
				root=$1;
				//printf("Answer : %d\n",evaluate($1));
				return;
				
			}
		;

expr : expr PLUS expr		{$$ = makeOperatorNode('+',$1,$3);}
	 | expr MINUS expr  	{$$ = makeOperatorNode('-',$1,$3);}
	 | expr MUL expr	{$$ = makeOperatorNode('*',$1,$3);}
	 | expr DIV expr	{$$ = makeOperatorNode('/',$1,$3);}
	 | '(' expr ')'		{$$ = $2;}
	 | NUM			{$$ = $1;}
	 ;

%%
int getReg(){
	int r=reg;
	reg++;
	if(r>20){
		printf("out of registers\n");
		exit(1);
	}
	return r;	
}
void freeReg(){
	reg--;
	if(reg<0){
		reg=0;
	}
	
}
int codeGen(struct tnode *root, FILE *targetfile){
	if(root==NULL) return -1;
	if(root->left==NULL && root->right==NULL){
		int r=getReg();
		fprintf(targetfile,"MOV R%d, %d\n",r,root->val);
		return r;
	}
	int i= codeGen(root->left,targetfile);
	int j= codeGen(root->right,targetfile);
	char c=*(root->op);
	switch(c){
		case '+':
			fprintf(targetfile,"ADD R%d, R%d\n",i,j);
			freeReg();
			break;
		case '-':
			fprintf(targetfile,"SUB R%d, R%d\n",i,j);
			freeReg();
			break;
		case '*':
			fprintf(targetfile,"MUL R%d, R%d\n",i,j);
			freeReg();
			break;
		case '/':
			fprintf(targetfile,"DIV R%d, R%d\n",i,j);
			freeReg();
	}
	return i;
	
}
yyerror(char const *s)
{
    printf("yyerror %s",s);
}
void prefix(struct tnode *root){
	if(root!=NULL){
		if(root->op!=NULL)
			printf("%c ",*(root->op));
		else
			printf("%d ",root->val);
		prefix(root->left);
		prefix(root->right);
	}
}
void postfix(struct tnode *root){
	if(root!=NULL){
		postfix(root->left);
		postfix(root->right);
		if(root->op!=NULL)
			printf("%c ",*(root->op));
		else
			printf("%d ",root->val);
		
	}
}
void print_start(){
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"2056\n");
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"0\n");
	fprintf(targetFile,"MOV SP,4096\n");
}
void printWrite(){
	fprintf(targetFile,"MOV R1, \"Write\"\nPUSH R1\nMOV R1, -2\nPUSH R1\nMOV R0,[4096]\nPUSH R0\nPUSH R1\nPUSH R1\nCALL 0\nPOP R0\nPOP R1\nPOP R1\nPOP R1\nPOP R1\nBRKP\n");
}
void printExit(){
	fprintf(targetFile,"MOV R1, \"Exit\"\nPUSH R1\nMOV R1, -1\nPUSH R1\nPUSH R0\nPUSH R1\nPUSH R1\nCALL 0\nPOP R0\nPOP R1\nPOP R1\nPOP R1\nPOP R1\n");
}
int main(int argc, char*argv[]) {
	targetFile=fopen("targetFile.xsm","w");

	yyin=fopen(argv[1],"r");
	yyparse();
	print_start();

	printf("prefix is : \n");
	prefix(root);
	printf("\npostfix is : \n");
	postfix(root);
	int r=codeGen(root,targetFile);
	fprintf(targetFile,"MOV [4096], R%d\n",r);
	fprintf(targetFile,"BRKP\n");
	printWrite();
	printExit();
	return 0;
}
