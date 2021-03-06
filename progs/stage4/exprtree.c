int reg=0;
int label_no=0;
int stacktop[20];	//for continue
int stackend[20];	//for break
int stack1=-1;		//for stacktop
int stack2=-1;		//for stackend
int addrbool=0;

struct tnode* createTree(int val, int type, char* c, int nodeType,struct Gsymbol*sym, struct tnode *l, struct tnode *r,struct tnode *third){
    switch(nodeType){
    	case tADD:
    	case tSUB:
    	case tMUL:
    	case tDIV:
    	case tMOD:
    		if(l->type!= r->type || l->type != tINT){
    			printf("type: %d %d %d\n",l->type,r->type,nodeType);
    			printf("\ntype mismatch error1\n");
    			exit(0);
    		}
    		else{
    			type=tINT;
    		}
    		break;
    	case tLT:
    	case tGT:
    	case tLE:
    	case tGE:
    	case tNE:
    	case tEQ:
    		if(l->type!= r->type || l->type !=tINT){
    			printf("type : %d %d\n",l->type,r->type);
    			printf("\ntype mismatch error2\n");
    			exit(0);
    		}
    		else{
    			type=tBOOL;
    		
    		}break;
    	case tASSIGN:
    		if(l->nodetype!=tVAR && l->nodetype!=tARRAY){
    			printf("\ntype mismatch error3\n");
    			exit(0);
    		}
    		break;
    	case tWHILE:
    	case tIF:
    		if(l->type!=tBOOL){
    			printf("\ntype mismatch error4\n");
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
    temp->Gentry=sym;
    temp->left=l;
    temp->right = r;
    temp->third=third;
    return temp;
}
int getSP(){
	struct Gsymbol* ptr;
	ptr=symbolRoot;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	return ptr->binding+ptr->size;
}
void updateSizeToLatestId(int size){
	struct Gsymbol* ptr;
	ptr=symbolRoot;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	ptr->size=size;
}
void printSymbolTable(){
	printf("symbol table\n");
	struct Gsymbol*ptr=symbolRoot;
	while(ptr!=NULL){
		printf("%s %d %d %d\n",ptr->name,ptr->type,ptr->size,ptr->binding);
		ptr=ptr->next;
	}
	return;
}
void install(char *name, int type, int size){

	struct Gsymbol*ptr;
	struct Gsymbol* temp = (struct Gsymbol*)malloc(sizeof(struct Gsymbol));
	temp->name=name;
	temp->type=type;
	temp->size=size;
	temp->next=NULL;
	//temp->next=symbolRoot;
	//symbolRoot=temp;
	//printSymbolTable();
	//return;
	
	ptr=symbolRoot;
	if(ptr==NULL){
		temp->binding=4096;
		symbolRoot=temp;
		return;
	}
	while(ptr->next!=NULL){
		if(strcmp(ptr->name,name)==0){
			printf("\nDuplicate variable declaration error\n");
			exit(0);
		}
		ptr=ptr->next;
	}
	if(strcmp(ptr->name,name)==0){
		printf("\nDuplicate variable declaration error\n");
		exit(0);
	}
	temp->binding=ptr->binding+ptr->size;
	ptr->next=temp;
	return;
}
struct Gsymbol *lookup(char * name){
	struct Gsymbol* temp=symbolRoot;
	while(temp!=NULL){
		if(strcmp(temp->name,name)==0)
		{
			//printf("%s\n",temp->name);
			return temp;
		}
		temp=temp->next;
	}
	printf("\nVAR name lookup missing error : %s\n",name);
	exit(0);
}
void symboltype(struct tnode* Type,struct tnode*Varlist){

	int type=Type->type;
	if(Varlist->varname==NULL){
		Varlist->right->Gentry->type=type;
		symboltype(Type,Varlist->left);
	}else{
		Varlist->Gentry->type=type;
	}
	//printSymbolTable();
}
void printExit(FILE* targetFile){
	fprintf(targetFile,"INT 10\n");
}
int getLabel(){
	int curr_label=label_no;
	label_no++;
	return curr_label;
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
void freeAllReg(){
	reg=0;
}
void printRead(FILE* targetFile, int varAddr){
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"Read\"\nPUSH R%d\nMOV R%d, -1\nPUSH R%d\nMOV R%d,%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\n",r,r,r,r,r,varAddr,r,r,r,r,r,r,r,r);
	freeReg();
}

void printReadReg(FILE* targetFile, int reg){
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"Read\"\nPUSH R%d\nMOV R%d, -1\nPUSH R%d\nMOV R%d,R%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\n",r,r,r,r,r,reg,r,r,r,r,r,r,r,r);
	freeReg();
}

void printWrite(FILE* targetFile, int regNum){
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"Write\"\nPUSH R%d\nMOV R%d, -2\nPUSH R%d\nMOV R%d,R%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nBRKP\n",r,r,r,r,r,regNum,r,r,r,r,r,r,r,r);
	freeReg();
}

int getVarAddr(struct tnode*root){
	char* varName=root->varname;
	int varAddr;
	if(root->val>-1){
		varAddr=root->Gentry->binding+ root->val;
	}else
		varAddr = root->Gentry->binding;
	return varAddr;
}

int codeGen(FILE* fp, struct tnode* root){
	int r,sourceReg,destReg,varAddr,label_1,label_2,label_3;
	char* varName;
	char* string;
	if(root==NULL) return -1;
	switch(root->nodetype){
		case tCONNECT: 
				freeAllReg();
				codeGen(fp,root->left);
				codeGen(fp,root->right);
				freeAllReg();
				return -1;
		case tREAD:
				if(root->left==NULL) {printf("\ninvalid read stmt\n");exit(0);}
				//varName = (root->left)->varname;
				if(root->left->nodetype!=tARRAY){
					varAddr = root->left->Gentry->binding;
					printRead(fp,varAddr);
				}else{
					destReg=codeGen(fp,root->left->left);
					r=getReg();
					fprintf(fp,"MOV R%d, %d\n",r,root->left->Gentry->binding);
					fprintf(fp,"ADD R%d, R%d\n",r,destReg);
					printReadReg(fp,r);
				}
				freeAllReg();
				return -1;
		case tNUM: 
				r=getReg();
				fprintf(fp,"MOV R%d, %d\n",r,root->val);
				return r;
		case tARRAY:
				r=getReg();
				destReg=codeGen(fp,root->left);
				if(root->Gentry==NULL) {printf("wow\n");exit(0);}
				fprintf(fp,"MOV R%d, %d\n",r,root->Gentry->binding);	
				//printf("%d\n",root->Gentry->binding);
				fprintf(fp,"ADD R%d, R%d\n",r,destReg);
				if(addrbool){
					return r;
				}else{
					fprintf(fp,"MOV R%d, [R%d]\n",r,r);
					return r;
				}
		case tVAR:
				r=getReg();
				varName=root->varname;
				varAddr = root->Gentry->binding;
				fprintf(fp,"MOV R%d,[%d]\n",r,varAddr);
				return r;
		case tWRITE:	
				r=codeGen(fp,root->left);
				printWrite(fp,r);
				freeAllReg();
				return -1;
		case tASSIGN:
				if(root->left->nodetype!=tARRAY){
					sourceReg=getVarAddr(root->left);
					if(root->right->type==tINT){
						destReg=codeGen(fp,root->right);
						fprintf(fp,"MOV [%d],R%d\n",sourceReg,destReg);
					}else{
						string=root->right->varname;
						fprintf(fp,"MOV [%d],%s\n",sourceReg,string);
					}
				}
				else{
					addrbool=1;
					sourceReg=codeGen(fp,root->left);
					addrbool=0;
					//fprintf(fp,"MOV R%d, %d\n",r,root->Gentry->binding);
					//fprintf(fp,"ADD R%d, R%d\n",r,destReg);
					if(root->right->type==tINT){
						destReg=codeGen(fp,root->right);
						fprintf(fp,"MOV [R%d],R%d\n",sourceReg,destReg);
					}else{
						string=root->right->varname;
						fprintf(fp,"MOV [R%d],%s\n",sourceReg,string);
					}
				}
				freeAllReg();
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
		case tMOD:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"MOD R%d,R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tLT:	
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"LT R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tGT:	
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"GT R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tLE:	
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"LE R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tGE:	
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"GE R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tNE:	
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"NE R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tBREAK:
				if(stack2<0) {printf("\ninvalid Break statement\n");exit(0);}
				fprintf(fp,"JMP L%d\n",stackend[stack2]);
				return -1;
		case tCONTINUE:
				if(stack1<0) {printf("\ninvalid continue statement\n");exit(0);}
				fprintf(fp,"JMP L%d\n",stacktop[stack1]);
				return -1;
		case tEQ:	
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"EQ R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;	
			
		case tWHILE:
				label_1 = getLabel();
				label_2 = getLabel();
				fprintf (fp, "L%d:\n", label_1); // Place the first label here.
				stack1++;
				stacktop[stack1]=label_1;
				stack2++;
				stackend[stack2]=label_2;
				sourceReg=codeGen(fp,root->left);
				fprintf(fp,"JZ R%d, L%d\n",sourceReg,label_2);
				codeGen(fp,root->right);
				fprintf(fp, "JMP L%d\n", label_1); // return to the beginning of the loop.
				fprintf(fp, "L%d:\n", label_2); // Place the second label here
				stack1--;
				stack2--;
				freeAllReg();
				return -1;
		case tIF:
				//label_1 = getLabel();
				if(root->third!=NULL)
					label_2 = getLabel();
				label_3 = getLabel();
				//fprintf (fp, "L%d:\n", label_1); // Place the first label here.
				//if
				sourceReg=codeGen(fp,root->left);
				if(root->third!=NULL)
					fprintf(fp,"JZ R%d, L%d\n",sourceReg,label_2);
				else
					fprintf(fp,"JZ R%d, L%d\n",sourceReg,label_3);
				//then
				codeGen(fp,root->right);
				fprintf(fp, "JMP L%d\n", label_3); // jump to endif.
				//else
				if(root->third!=NULL){
					fprintf(fp, "L%d:\n", label_2); // Place the second label here
					//else
					codeGen(fp,root->third);
					fprintf(fp, "JMP L%d\n", label_3); // jump to endif.	
				}
				fprintf(fp, "L%d:\n", label_3); // Place the third label here
				freeAllReg();
				return -1;
		defualt:
				printf("\nsome error in codegen fn : %d\n",root->nodetype);
				exit(0);		
	}
}













