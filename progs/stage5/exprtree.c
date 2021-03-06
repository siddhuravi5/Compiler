int reg=1;
int label_no=0;
int stacktop[20];	//for continue
int stackend[20];	//for break
int stack1=-1;		//for stacktop
int stack2=-1;		//for stackend
int addrbool=0;
int fnlocalvarbinding=0;
int fnargumentsbinding=-2;

int getLabel(){
	int curr_label=label_no;
	label_no++;
	return curr_label;
}
void reset_fnargumentsbinding(){
	fnargumentsbinding=-2;
	fnlocalvarbinding=0;
	return;
}
struct tnode* createTree(int val, int type, char* c, int nodeType,struct Lsymbol* Lsym,struct Gsymbol* Gsym, struct tnode *l, struct tnode *r,struct tnode *third){
    switch(nodeType){
    	case tVAR:
    		//printf("%s\n",Lsym->name);
    		break;
    	case tADD:
    	case tSUB:
    	case tMUL:
    	case tDIV:
    	case tMOD:
    		type=tINT;
    		/*if(l->type!= r->type || l->type != tINT){
    			printf("type: %d %d %d\n",l->type,r->type,nodeType);
    			printf("\ntype mismatch error1\n");
    			exit(0);
    		}
    		else{
    			type=tINT;
    		}*/
    		break;
    	case tLT:
    	case tGT:
    	case tLE:
    	case tGE:
    	case tNE:
    	case tEQ:
    		type=tBOOL;
    		/*if(l->type!= r->type || l->type !=tINT){
    			printf("type : %d %d\n",l->type,r->type);
    			printf("\ntype mismatch error2\n");
    			exit(0);
    		}
    		else{
    			type=tBOOL;
    		
    		}*/
    		break;
    	case tASSIGN:
    		/*if(l->nodetype!=tVAR && l->nodetype!=tARRAY){
    			printf("\ntype mismatch error3\n");
    			exit(0);
    		}*/
    		break;
    	case tWHILE:
    	case tIF:
    		/*if(l->type!=tBOOL){
    			printf("\ntype mismatch error4\n");
    			exit(0);
    		}*/
    		break;
    }
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->val = val;
    temp->type = type;
    temp->varname = c;
    temp->nodetype = nodeType;
    temp->Lentry=Lsym;
    temp->Gentry=Gsym;
    temp->left=l;
    temp->right = r;
    temp->third=third;
    return temp;
}

struct Paramstruct* createParam(char* name,int type){
	struct Paramstruct* tmp=(struct Paramstruct*)malloc(sizeof(struct Paramstruct));
	tmp->name=name;
	tmp->type=type;
	tmp->next=NULL;
	return tmp;
}

struct Paramstruct* addParam(struct Paramstruct* root,struct Paramstruct* elt){
	struct Paramstruct* ptr=root;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	ptr->next=elt;
	return root;
}

void Ginstall(char* name,int type,int size,int binding,struct Paramstruct* paramlist,int flabel){
	struct Gsymbol* temp=(struct Gsymbol*)malloc(sizeof(struct Gsymbol));
	temp->name=name;
	temp->type=type;
	temp->size=size;
	temp->binding=binding;
	temp->paramlist=paramlist;
	temp->flabel=flabel;
	temp->next=NULL;
	
	int label;
	
	struct Gsymbol* ptr=Gsymbolroot;
	struct Gsymbol* ptr2=Gsymbolroot;
	if(ptr==NULL){
		if(size!=-1)	//variable check
			temp->binding=4096;
		else{	//fn
			label=getLabel();
			temp->flabel=label;
		}
		Gsymbolroot=temp;
		return;
	}
	while(ptr->next!=NULL){
		if(strcmp(ptr->name,name)==0){
			printf("\nDuplicate variable/fn declaration error\n");
			exit(0);
		}
		ptr=ptr->next;
	}
	if(strcmp(ptr->name,name)==0){
		printf("\nDuplicate variable/function declaration error\n");
		exit(0);
	}
	if(size!=-1){ //variable check
		
		int bindaddr=4096;
		while(ptr2!=NULL){
			if(ptr2->size!=-1){
				bindaddr=ptr2->binding+ptr2->size;
			}
			ptr2=ptr2->next;
		}
		temp->binding=bindaddr;
	}else{	//fn
		label=getLabel();
		temp->flabel=label;
	}
	ptr->next=temp;
	return;
}
void updateTypeToGsymbol(int type){
	struct Gsymbol* ptr;
	ptr=Gsymbolroot;
	while(ptr!=NULL){
		if(ptr->type==-1){
			ptr->type=type;
		}
		ptr=ptr->next;
	}
}
void printGsymbolTable(){
	printf("Global Symbol Table\n");
	struct Gsymbol*ptr=Gsymbolroot;
	struct Paramstruct* tmp;
	while(ptr!=NULL){
		printf("%s %d %d %d F%d\n",ptr->name,ptr->type,ptr->size,ptr->binding,ptr->flabel);
		tmp=ptr->paramlist;
		while(tmp!=NULL){
			printf("	%s %d\n",tmp->name,tmp->type);
			tmp=tmp->next;
		}
		ptr=ptr->next;
	}
	return;
}
void Lprint(){
	printf("Local Symbol Table\n");
	struct Lsymbol*ptr=Lsymbolroot;
	while(ptr!=NULL){
		printf("%s %d %d\n",ptr->name,ptr->type,ptr->binding);
		ptr=ptr->next;
	}
	return;
}
void Linstallbylist(struct Paramstruct* root){
	struct Lsymbol* tmp,*ptr;
	ptr=Lsymbolroot;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	while(root!=NULL){
		tmp=(struct Lsymbol*)malloc(sizeof(struct Lsymbol));
		tmp->name=root->name;
		tmp->type=root->type;
		tmp->binding=(--fnargumentsbinding);
		tmp->next=NULL;
		if(Lsymbolroot==NULL){
			Lsymbolroot=tmp;
			ptr=Lsymbolroot;
		}else{
			ptr->next=tmp;
			ptr=ptr->next;
		}
		root=root->next;
	}
	
}
void Linstallbylistwithtype(struct Paramstruct* root, int type){		//inserting local variables
	struct Lsymbol* tmp,*ptr;
	ptr=Lsymbolroot;
	if(ptr){
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
	}
	while(root!=NULL){
		tmp=(struct Lsymbol*)malloc(sizeof(struct Lsymbol));
		tmp->name=root->name;
		tmp->type=type;
		tmp->binding=(++fnlocalvarbinding);
		tmp->next=NULL;
		if(Lsymbolroot==NULL){
			Lsymbolroot=tmp;
			ptr=Lsymbolroot;
		}else{
			ptr->next=tmp;
			ptr=ptr->next;
		}
		root=root->next;
	}
}
void Linstall(char* name, int type){
	printf("---------------------\n");
	struct Lsymbol* tmp=(struct Lsymbol*)malloc(sizeof(struct Lsymbol));
	tmp->name = name;
	tmp->type=type;
	tmp->binding=(--fnargumentsbinding);
	if(Lsymbolroot==NULL){
		Lsymbolroot=tmp;
		return;
	}
	struct Lsymbol* ptr=Lsymbolroot;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	ptr->next=tmp;
	return;
}
struct Lsymbol* Llookup(char* name){
	struct Lsymbol* ptr = Lsymbolroot;
	while(ptr!=NULL){
		//printf("%s %s\n",ptr->name,name);
		if(strcmp(ptr->name,name)==0){
			return ptr;
		}
		//printf("%s %s\n",ptr->name,name);
		ptr=ptr->next;
	}
	return NULL;
}
struct Gsymbol* Glookup(char* name){
	struct Gsymbol* tmp=Gsymbolroot;
	while(tmp!=NULL){
		if(strcmp(tmp->name,name)==0){
			return tmp;	
		}
		tmp=tmp->next;
	}
	return NULL;
}
struct tnode* appendArgList(struct tnode* root, struct tnode* elt){
	struct tnode* ptr=root;
	while(root->third!=NULL){
		root=root->third;
	}
	root->third=elt;
	return root;
}
int getSP(){
	struct Gsymbol* ptr;
	ptr=Gsymbolroot;
	int spval=4096;
	while(ptr!=NULL){
		if(ptr->binding!=-1){
			spval=ptr->binding+ptr->size;
		}
		ptr=ptr->next;
	}
	return spval;
}
/*
void updateSizeToLatestId(int size){
	struct Gsymbol* ptr;
	ptr=Gsymbolroot;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	ptr->size=size;
}
*/
void printSymbolTable(){
	printf("symbol type\n");
	struct Gsymbol*ptr=Gsymbolroot;
	while(ptr!=NULL){
		printf("%s %d %d %d\n",ptr->name,ptr->type,ptr->size,ptr->binding);
		ptr=ptr->next;
	}
	return;
}
/*
void install(char *name, int type, int size){

	struct Gsymbol*ptr;
	struct Gsymbol* temp = (struct Gsymbol*)malloc(sizeof(struct Gsymbol));
	temp->name=name;
	temp->type=type;
	temp->size=size;
	temp->next=NULL;
	//temp->next=Gsymbolroot;
	//Gsymbolroot=temp;
	//printSymbolTable();
	//return;
	
	ptr=Gsymbolroot;
	if(ptr==NULL){
		temp->binding=4096;
		Gsymbolroot=temp;
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
*/
/*
struct Gsymbol *lookup(char * name){
	struct Gsymbol* temp=Gsymbolroot;
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
*/
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

int getVarAddr(FILE* fp,struct tnode*root){
	char* varName=root->varname;
	int varAddr;
	int s;
	if(root->val>-1){ //array
		varAddr=root->Gentry->binding+ root->val;
	}else{
		if(root->Lentry){
			s=getReg();
			varAddr = root->Lentry->binding;
			fprintf(fp,"MOV R%d, %d\n",s,varAddr);
			fprintf(fp,"ADD R%d, BP\n",s);
			return s;
		}
		else
			varAddr = root->Gentry->binding;		
	}
	return varAddr;
}

int codeGen(FILE* fp, struct tnode* root){
	int r,s,regcount[20],regptr=-1,sourceReg,destReg,varAddr,label_1,label_2,label_3;
	char* varName;
	char* string;
	struct Lsymbol* ptr;
	struct Gsymbol* tmp;
	struct tnode* node;
	if(root==NULL) return -1;
	switch(root->nodetype){
		
		case tFBODY:
				freeAllReg();
				if(root->varname==NULL || (root->right && root->right->val==tMAINLabel)){
					//printf("main");
					fprintf(fp,"L%d:\n",tMAINLabel);
					s=getSP();
					fprintf(fp,"MOV SP, %d\n",s);
				}else{
					tmp=Gsymbolroot;
					while(tmp!=NULL && strcmp(tmp->name,root->varname)!=0){
						printf("%s\n",tmp->name);
						tmp=tmp->next;
					}
					if(tmp==NULL){
						printf("%s\n",root->varname);
						printf("Undeclared fn error\n");
						exit(0);
					}
					fprintf(fp,"L%d:\n",tmp->flabel);
				}
				fprintf(fp,"PUSH BP\n");
				fprintf(fp,"MOV BP,SP\n");
				ptr=Lsymbolroot;
				//reserve space for local variables NOt for arguments
				while(ptr!=NULL){
					if(ptr->binding>0)
						fprintf(fp,"PUSH R0\n");
					ptr=ptr->next;
				}
				codeGen(fp,root->left);
				codeGen(fp,root->right);
				freeAllReg();
				return -1;
		case tRET:
				if(root->val!=tMAINLabel){
					destReg=codeGen(fp,root->left);
					//save return value
					s=getReg();
					fprintf(fp,"MOV R%d,BP\n",s);
					fprintf(fp,"SUB R%d,2\n",s);
					fprintf(fp,"MOV [R%d],R%d\n",s,destReg);
				}
				ptr=Lsymbolroot;
				//remove space allocated for local variables
				while(ptr!=NULL){
					if(ptr->binding>0)
						fprintf(fp,"POP R0\n");
					ptr=ptr->next;
				}
				//restore old value of BP
				fprintf(fp,"POP BP\n");
				if(root->val==tMAINLabel){
					printExit(fp);
				}else{
					fprintf(fp,"RET\n");
				}
				
				return -1;
		case tFUNC:
				node=root->left;	//1st arg (can be null also)
				int argArray[25];
				int argArrayInd=-1;
				
				while(node!=NULL){
					sourceReg=codeGen(fp,node);
					argArray[(++argArrayInd)]=sourceReg;
					node=node->third;	//arg list
				}
				//push registers in use
				++regptr;
				regcount[regptr]=reg;
				for(int j=0;j<regcount[regptr];j++){
					fprintf(fp,"PUSH R%d\n",j);
				}
				//push arguments to fn in reverse order
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"PUSH R%d\n",argArray[j]);
				}
				//push empty space for return value
				fprintf(fp,"PUSH R0\n");
				fprintf(fp,"CALL L%d\n",root->Gentry->flabel);
				
				//after returning from fn call
				
				sourceReg= getReg();
				//save the result
				fprintf(fp,"MOV R%d,[SP]\n",sourceReg);
				//pop out result space
				fprintf(fp,"POP R0\n");
				//pop out args from stack
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"POP R0\n");
				}
				
				//restore machine registers
				for(int j=regcount[regptr]-1;j>=0;j--){
					fprintf(fp,"POP R%d\n",j);
				}
				regptr--;
				return sourceReg;
				
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
					if(root->left->Lentry){
						varAddr= root->left->Lentry->binding;
						r=getReg();
						fprintf(fp,"MOV R%d, BP\n",r);
						fprintf(fp,"ADD R%d,%d\n",r,varAddr);
						//fprintf(fp,"MOV R%d,r\n",r,varAddr);
						printReadReg(fp,r);
					}else{
						varAddr = root->left->Gentry->binding;
						printRead(fp,varAddr);
					}
					
				}else{
					//array
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
				if(root->Gentry==NULL) {printf("array not in Gsymbol\n");exit(0);}
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
	
				if(root->Lentry!=NULL){
					varAddr = root->Lentry->binding;
					s=getReg();
					fprintf(fp,"MOV R%d,BP\n",s);
					fprintf(fp,"ADD R%d,%d\n",s,varAddr);
					fprintf(fp,"MOV R%d,[R%d]\n",r,s);
				}else{
					if(root->Gentry==NULL){
						printf("Undeclared variable used error\n");
					}
					varAddr = root->Gentry->binding;
					fprintf(fp,"MOV R%d,[%d]\n",r,varAddr);
				}
				return r;
		case tWRITE:	
				r=codeGen(fp,root->left);
				printWrite(fp,r);
				freeAllReg();
				return -1;
		case tASSIGN:
				if(root->left->nodetype!=tARRAY){
					sourceReg=getVarAddr(fp,root->left);
					if(root->right->type!=tSTR){
						destReg=codeGen(fp,root->right);
						if(sourceReg<25){
							fprintf(fp,"MOV [R%d],R%d\n",sourceReg,destReg);	//BP relative addr
						}else{
							fprintf(fp,"MOV [%d],R%d\n",sourceReg,destReg);
						}
					}else{
						string=root->right->varname;
						if(sourceReg<25){
							//printf("CCCCCCCc\n");
							fprintf(fp,"MOV [R%d],%s\n",sourceReg,string);	//BP relative addr
						}else{
							fprintf(fp,"MOV [%d],%s\n",sourceReg,string);
						}
					}
				}
				else{
					//array
					addrbool=1;
					sourceReg=codeGen(fp,root->left);
					addrbool=0;
					//fprintf(fp,"MOV R%d, %d\n",r,root->Gentry->binding);
					//fprintf(fp,"ADD R%d, R%d\n",r,destReg);
					if(root->right->type!=tSTR){
						destReg=codeGen(fp,root->right);
						fprintf(fp,"MOV [R%d],R%d\n",sourceReg,destReg);
					}else{
						string=root->right->varname;
						//printf("ZZZZZZ\n");
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
		case tAND:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"MUL R%d, R%d\n",sourceReg,destReg);
				freeReg();
				return sourceReg;
		case tOR:
				sourceReg=codeGen(fp,root->left);
				destReg=codeGen(fp,root->right);
				fprintf(fp,"ADD R%d, R%d\n",sourceReg,destReg);
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













