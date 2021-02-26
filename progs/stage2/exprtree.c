int reg=0;
struct tnode* createTree(int val, int type, char* c, int nodeType, struct tnode *l, struct tnode *r){
    switch(nodeType){
    	case tADD:
    	case tSUB:
    	case tMUL:
    	case tDIV:
    		if(l->type!= r->type || l->type != tINT){
    			printf("type mismatch error 1\n");
    			exit(0);
    		}
    		else{
    			type=tINT;
    		}
    		break;
    	case tASSIGN:
    		if(r->type!=tINT || l->nodetype!=tVAR){
    			printf("type mismatch error 2\n");
    			exit(0);
    		}
    		break;
    }
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->val = val;
    temp->type = type;
    temp->varname = c;
    temp->nodetype = nodeType;
    temp->left=l;
    temp->right = r;
    return temp;
}



void printExit(FILE* targetFile){
	fprintf(targetFile,"INT 10\n");
}

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
void printRead(FILE* targetFile, int varAddr){
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"Read\"\nPUSH R%d\nMOV R%d, -1\nPUSH R%d\nMOV R%d,%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\n",r,r,r,r,r,varAddr,r,r,r,r,r,r,r,r);
	freeReg();
}

void printWrite(FILE* targetFile, int regNum){
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"Write\"\nPUSH R%d\nMOV R%d, -2\nPUSH R%d\nMOV R%d,R%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nBRKP\n",r,r,r,r,r,regNum,r,r,r,r,r,r,r,r);
	freeReg();
}

int getVarAddr(struct tnode*root){
	char* varName=root->varname;
	int varAddr = 4096 + (varName[0] - 'a');
	return varAddr;
}

int codeGen(FILE* fp, struct tnode* root){
	printf("code fn");
	int r,sourceReg,destReg,varAddr;
	char* varName;
	if(root==NULL) return -1;
	switch(root->nodetype){
		case tCONNECT: 
				codeGen(fp,root->left);
				codeGen(fp,root->right);
				return -1;
		case tREAD:
				if(root->left==NULL) {printf("invalid read stmt\n");exit(0);}
				varName = (root->left)->varname;
				varAddr= 4096 + (varName[0] - 'a');
				printf("var addr = %d\n",varAddr);
				printRead(fp,varAddr);
				return -1;
		case tNUM: 
				r=getReg();
				fprintf(fp,"MOV R%d, %d\n",r,root->val);
				return r;
		case tVAR:
				r=getReg();
				varName=root->varname;
				varAddr = 4096 + (varName[0] - 'a');
				fprintf(fp,"MOV R%d,[%d]\n",r,varAddr);
				return r;
		case tWRITE:	
				r=codeGen(fp,root->left);
				printWrite(fp,r);
				return -1;
		case tASSIGN:
				sourceReg=getVarAddr(root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"MOV [%d],R%d\n",sourceReg,destReg);
				return -1;
		case tADD:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"ADD R%d,R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tSUB:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"SUB R%d,R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tMUL:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"MUL R%d,R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tDIV:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"DIV R%d,R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		defualt:
				printf("some error in codegen fn\n");
				exit(0);		
	}
}













