int reg=0;
int label_no=0;
int stacktop[20];	//for continue
int stackend[20];	//for break
int stack1=-1;		//for stacktop
int stack2=-1;		//for stackend
int addrbool=0;
int fnlocalvarbinding=0;
int fnargumentsbinding=-2;
int dynamicbinding=2047;
int SPTOP=4096;

struct Typetable* typeroot=NULL;

void virtualFuncTableInit(FILE*fp,FILE* dp){
	struct Classtable* ptr=classroot;
	struct Memberfunclist* f1;
	int bind=4096;
	int r=getReg();
	while(ptr!=NULL){
		bind=4096+ptr->Class_index*8;
		f1=ptr->Vfuncptr;
		while(f1!=NULL){
			fprintf(fp,"MOV R%d,%d\n",r,bind);
			fprintf(fp,"MOV [R%d],%d\n",r,f1->Flabel);

			fprintf(dp,"%d\n",bind);
			fprintf(dp,"%d\n",f1->Flabel);
			bind++;
			f1=f1->next;
		}
		ptr=ptr->next;
	}
	fprintf(dp,"-10\n");
}

int classIndex(char*name){
	struct Classtable* ptr=classroot;
	while(ptr!=NULL){
		if(strcmp(ptr->name,name)==0){
			return ptr->Class_index;
		}
		ptr=ptr->next;
	}
	printf("invalid class name for inheritance\n");
	exit(0);
}

int getBindingForMethod2(char* name1,char* name2){
	struct Gsymbol* g=Glookup(name1);
	struct Classtable* c=g->Ctype;
	struct Fieldlist* f1;
	f1=c->memberfield;
	while(f1!=NULL){
		if(strcmp(f1->name,name2)==0){
			return f1->fieldIndex;
		}
		f1=f1->next;
	}
}

struct Typetable* findclassmemtype(char* cname,char* type){
	struct Classtable* c1=Clookup(cname);
	struct Fieldlist* f1=c1->memberfield;
	while(f1!=NULL){
		if(strcmp(f1->name,type)==0){
			//printf("zzz->%s",f1->type->name);
			return f1->type;
		}
		f1=f1->next;
	}
	printf("a.b.c error\n");
	exit(0);
}

void Cinstall(char*name,char* parent){
	struct Classtable* ptr=(struct Classtable*)malloc(sizeof(struct Classtable));
	ptr->name=name;
	ptr->next=NULL;
	ptr->memberfield=NULL;
	ptr->Vfuncptr=NULL;
	ptr->Fieldcount=0;
	ptr->Methodcount=0;
	if(parent!=NULL){
		//inheritance
		ptr->Parentptr=Clookup(parent);
		ptr->Fieldcount=ptr->Parentptr->Fieldcount;
		ptr->Methodcount=ptr->Parentptr->Methodcount;
		//field copying from parent class
		struct Fieldlist *f1,*f2,*f3,*f4;
		f1=ptr->Parentptr->memberfield;
		f3=NULL;
		while(f1!=NULL){
			f2=(struct Fieldlist *)malloc(sizeof(struct Fieldlist));
			f2->name=f1->name;
			f2->type=f1->type;
			f2->Ctype=f1->Ctype;
			f2->fieldIndex=f1->fieldIndex;
			f2->next=NULL;
			if(f3==NULL){
				f3=f2;
			}else{
				f4=f3;
				while(f4->next!=NULL){
					f4=f4->next;
				}
				f4->next=f2;
			}
			f1=f1->next;
		}
		ptr->memberfield=f3;

		//method copying from parent class
		struct Memberfunclist *m1,*m2,*m3,*m4;
		m1=ptr->Parentptr->Vfuncptr;
		m3=NULL;
		while(m1!=NULL){
			m2=(struct Memberfunclist *)malloc(sizeof(struct Memberfunclist));
			m2->name=m1->name;
			m2->type=m1->type;
			m2->Funcposition=m1->Funcposition;
			m2->Flabel=m1->Flabel;
			m2->paramlist=m1->paramlist;
			m2->next=NULL;
			if(m3==NULL){
				m3=m2;
			}else{
				m4=m3;
				while(m4->next!=NULL){
					m4=m4->next;
				}
				m4->next=m2;
			}
			m1=m1->next;
		}
		ptr->Vfuncptr=m3;
		//ptr->Vfuncptr=ptr->Parentptr->Vfuncptr;
	}
	else
		ptr->Parentptr=NULL;
	struct Classtable* tmp;
	if(classroot==NULL){
		ptr->Class_index=0;
		classroot=ptr;
	}else{
		tmp=classroot;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		ptr->Class_index=tmp->Class_index+1;
		tmp->next=ptr;
	}
}

struct Classtable* Clookup(char* name){
	struct Classtable* ptr=classroot;
	while(ptr!=NULL){
		//printf("%s z %s\n",ptr->name,name);
		if(strcmp(ptr->name,name)==0){
			//printf("class found\n");
			return ptr;
		}
		ptr=ptr->next;
	}
	return NULL;
}

void ClassFinstall(char* name1, char* name2){
	struct Classtable* ptr=classroot;
	struct Fieldlist* f1,*f2;
	f1=(struct Fieldlist*)malloc(sizeof(struct Fieldlist));
	f1->name=name2;
	f1->type=typelookuponly(name1);
	f1->Ctype=Clookup(name1);
	f1->next=NULL;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	//ptr points to the current class
	ptr->Fieldcount=ptr->Fieldcount+1;
	if(ptr->Fieldcount>8){
		printf("More than 8 fields are declared for a class\n");
		exit(0);
	}
	f2=ptr->memberfield;
	if(f2==NULL){
		f1->fieldIndex=0;
		ptr->memberfield=f1;
	}else{
		while(f2->next!=NULL){
			f2=f2->next;
		}
		f1->fieldIndex=f2->fieldIndex+1;
		f2->next=f1;
	}
}

void ClassMinstall(struct Typetable* type,char* name,struct Paramstruct* params){
	int methodOverriding=0;
	struct Memberfunclist*f1,*f2;
	struct Classtable* ptr=classroot;
	f1=(struct Memberfunclist*)malloc(sizeof(struct Memberfunclist));
	f1->name=name;
	f1->type=type;
	f1->paramlist=params;
	f1->next=NULL;
	int l=getLabel();
	f1->Flabel=l;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	//ptr points to the current class
	f2=ptr->Vfuncptr;
	if(f2==NULL){
		f1->Funcposition=0;
		ptr->Vfuncptr=f1;
	}else{
		while(f2!=NULL){
			if(strcmp(f2->name,f1->name)==0){
				methodOverriding=1; //set to true
				f2->Flabel=getLabel();
				//free(f1);	//no need of f1 as we are method overriding
				break;
			}
			f2=f2->next;
		}
		if(methodOverriding==0){
			f2=ptr->Vfuncptr;
			if(f1==NULL || f2==NULL){
				exit(0);
			}
			while(f2->next!=NULL){
				f2=f2->next;
			}
		}
		if(methodOverriding==0){
			//printf("-->%s\n",f1->name);
			f1->Funcposition=f2->Funcposition+1;
			f2->next=f1;
		}
	}
	if(methodOverriding==0){
		ptr->Methodcount=ptr->Methodcount+1;
	}
	if(ptr->Methodcount>8){
		printf("More than 8 methods are declared for a class\n");
		exit(0);
	}
}

struct Typetable* fieldtypelookup(char* name1,char* name2){
	struct Typetable* tmp=typelookup(name1);
	//printf("%s\n",tmp->name);
	struct Fieldlist* f=tmp->fields;
	while(f!=NULL){
		//printf("%s, %s\n",f->name,name2);
		if(strcmp(f->name,name2)==0){
			return f->type;
		}
		f=f->next;
	}
	printf("\nundeclared type var3\n");
	exit(0);
}
struct Typetable* fieldtype(char* name1,char* name2){
	struct Lsymbol* ptr=Llookup(name1);
	struct Gsymbol* ptr2=Glookup(name1);
	struct Typetable* tmp;
	if(ptr!=NULL){
		tmp=ptr->type;
	}else{
		if(ptr2==NULL){
			//printf("%s\n",name1);
			printf("\nundeclared type var\n");
			exit(0);
		}
		tmp=ptr2->type;
	}
	struct Fieldlist* f=tmp->fields;
	while(f!=NULL){
		//printf("%s\n",f->name);
		if(strcmp(f->name,name2)==0){
			return f->type;
		}
		f=f->next;
	}
	printf("\nundeclared type var2\n");
	exit(0);
}

struct Fieldlist* fieldinstall(char* name,struct Typetable* type){
	struct Fieldlist* ptr;
	ptr= (struct Fieldlist*) malloc(sizeof(struct Fieldlist));
	ptr->name=name;
	ptr->type=type;
	//ptr->fieldIndex=0;
	return ptr;
}
struct Fieldlist* fieldappend(struct Fieldlist* root,struct Fieldlist* elt){
	struct Fieldlist* ptr=root;
	while(ptr->next!=NULL){
		ptr=ptr->next;
	}
	elt->fieldIndex=ptr->fieldIndex+1;
	ptr->next=elt;
	return root;
}
void typeinstallwithfields(char* name,int size, struct Fieldlist *fields){
	struct Typetable* ptr;
	ptr=typelookup(name);
	ptr->size=size;
	ptr->fields=fields;
}
void typeinstall(char* name){
	struct Typetable* ptr,*tmp;
	ptr= (struct Typetable*) malloc(sizeof(struct Typetable));
	ptr->name=name;
	ptr->next=NULL;
	if(typeroot==NULL){
		typeroot=ptr;
	}else{
		tmp=typeroot;
		while(tmp->next!=NULL){
			tmp=tmp->next;
		}
		tmp->next=ptr;
	}
}

struct Typetable* typelookuponly(char* name){
	struct Typetable* ptr=typeroot;
	while(ptr!=NULL){
		//printf("%s z %s\n",ptr->name,name);
		if(strcmp(ptr->name,name)==0){
			return ptr;
		}
		ptr=ptr->next;
	}
	return NULL;
}

struct Typetable* typelookup(char*name){
	struct Typetable* ptr=typeroot;
	while(ptr!=NULL){
		//printf("%s z %s\n",ptr->name,name);
		if(strcmp(ptr->name,name)==0){
			return ptr;
		}
		ptr=ptr->next;
	}
	typeinstall(name);
	return typelookup(name);
	printf("\nType not defined priorly\n");
	exit(0);
}
void printTypeTable(){
	struct Typetable* ptr=typeroot;
	printf("TYPE TABLE\n");
	int i=0;
	while(ptr!=NULL){
		printf("%s\n",ptr->name);
		ptr=ptr->next;
		i++;
		if(i>12) break;
	}
	printf("--------------\n");
}
struct Typetable* typesearch(char *name){
	struct Lsymbol* ptr=Llookup(name);
	struct Gsymbol* ptr2=Glookup(name);
	if(ptr!=NULL){
		return ptr->type;	
	}else{
		if(ptr2==NULL){
			printf("\n%s\n",name);
			printf("\nUndeclared variable used\n");
			exit(0);
		}
		return ptr2->type;
	}
}

void functypecheck(struct Paramstruct* params, struct Gsymbol* fn){
	struct Paramstruct* args=fn->paramlist;
	struct Paramstruct *ptr,*tmp;
	ptr=params;
	tmp=args;
	while(ptr && tmp){
		if(strcmp(ptr->name,tmp->name)!=0 || ptr->type!=tmp->type){
			printf("\nglobal fn declaration and fn defn does not match\n");
			exit(0);
		}
		ptr=ptr->next;
		tmp=tmp->next;
	}
}

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
struct tnode* createTree(int val, struct Typetable* type, char* c, int nodeType,struct Lsymbol* Lsym,struct Gsymbol* Gsym, struct tnode *l, struct tnode *r,struct tnode *third,struct Classtable* Centry){
    switch(nodeType){
    	case tVAR:
    		//printf("%s\n",Lsym->name);
    		break;
    	case tADD:
    	case tSUB:
    	case tMUL:
    	case tDIV:
    	case tMOD:
    		type=typelookup("int");
    		/*if(l->type!= r->type){
    			//printf("type: %d %d %d\n",l->type,r->type,nodeType);
    			printf("\ntype mismatch error1\n");
    			exit(0);
    		}
    		else{
    			type=typelookup("tINT");
    		}*/
    		break;
    	case tLT:
    	case tGT:
    	case tLE:
    	case tGE:
    	case tNE:
    	case tEQ:
    		//type=tBOOL;
    		/*if(l->type!= r->type || l->type !=typelookup("int")){
    			//printf("type : %d %d\n",l->type,r->type);
    			printf("\ntype mismatch error2\n");
    			exit(0);
    		}
    		else{
    			type=typelookup("bool");
    		
    		}*/
    		type=typelookup("bool");
    		break;
    	case tASSIGN:
    		/*if(l->nodetype!=tVAR && l->nodetype!=tARRAY){
    			printf("\ntype mismatch error3\n");
    			exit(0);
    		}*/
    		break;
    	case tWHILE:
    	case tIF:
    		if(l->type!=typelookup("bool")){
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
    temp->Lentry=Lsym;
    temp->Gentry=Gsym;
    temp->left=l;
    temp->right = r;
    temp->third=third;
    temp->Ctype=Centry;
    return temp;
}

struct Paramstruct* createParam(char* name,struct Typetable* type){
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

void Ginstall(char* name,struct Typetable* type,int size,int binding,struct Paramstruct* paramlist,int flabel){
	struct Gsymbol* temp=(struct Gsymbol*)malloc(sizeof(struct Gsymbol));
	temp->name=name;
	temp->type=type;
	temp->Ctype=NULL;
	temp->size=size;
	temp->binding=binding;
	temp->paramlist=paramlist;
	temp->flabel=flabel;
	temp->next=NULL;
	
	int bind=4096;
	struct Classtable* c1= classroot;
	while(c1!=NULL){
		bind+=8;	//every class a virtual fn table of size 8 words
		c1=c1->next;
	}
	int label;
	
	struct Gsymbol* ptr=Gsymbolroot;
	struct Gsymbol* ptr2=Gsymbolroot;
	if(ptr==NULL){
		if(size!=-1){	//variable check
			temp->binding=bind;
		}
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
		
		int bindaddr=bind;
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
void updateBinding(){
	struct Gsymbol* ptr=Gsymbolroot,*p;
	int bind=4096;
	struct Classtable* c1= classroot;
	while(c1!=NULL){
		bind+=8;	//every class a virtual fn table of size 8 words
		c1=c1->next;
	}
	p=Gsymbolroot;
	while(ptr!=NULL){
		if(ptr->size>0){
			ptr->binding=bind;
			bind+=ptr->size;
		}
		ptr=ptr->next;
	}
	SPTOP=bind;
}
void updateTypeToGsymbol(char* type){
	if(Clookup(type)!=NULL){
		//object types (class variables)
		struct Gsymbol* ptr;
		ptr=Gsymbolroot;
		while(ptr!=NULL){
			if(ptr->type==NULL && ptr->Ctype==NULL){
				ptr->type=NULL;
				ptr->size=2;
				ptr->Ctype=Clookup(type);
			}
			ptr=ptr->next;
		}
	}else{
		//other types
		struct Gsymbol* ptr;
		ptr=Gsymbolroot;
		while(ptr!=NULL){
			if(ptr->type==NULL && ptr->Ctype==NULL){
				ptr->type=typelookuponly(type);
				ptr->Ctype=NULL;
			}
			ptr=ptr->next;
		}
	}

}
void printGsymbolTable(){
	printf("Global Symbol Table\n");
	struct Gsymbol*ptr=Gsymbolroot;
	struct Paramstruct* tmp;
	while(ptr!=NULL){
		printf("%s %d %d F%d\n",ptr->name,ptr->size,ptr->binding,ptr->flabel);
		tmp=ptr->paramlist;
		while(tmp!=NULL){
			printf("	%s\n",tmp->name);
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
		printf("%s %d\n",ptr->name,ptr->binding);
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
void Linstallbylistwithtype(struct Paramstruct* root, struct Typetable* type){		//inserting local variables
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
void Linstall(char* name, struct Typetable* type){
	//printf("---------------------\n");
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
	while(ptr->third!=NULL){
		ptr=ptr->third;
	}
	ptr->third=elt;
	return root;
}
int getSP(){
	return SPTOP;
	/*struct Gsymbol* ptr;
	ptr=Gsymbolroot;
	int spval=4096;
	while(ptr!=NULL){
		if(ptr->binding!=-1){
			spval=ptr->binding+ptr->size;
		}
		ptr=ptr->next;
	}
	return spval;
	*/
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
		printf("%s %d %d\n",ptr->name,ptr->size,ptr->binding);
		ptr=ptr->next;
	}
	return;
}
/*
void install(char *name, struct Typetable* type, int size){

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

	struct Typetable* type=Type->type;
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
int printAlloc(FILE* targetFile){
	//fprintf(targetFile,"PUSH R1\n");
	int s=getReg();
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"alloc\"\nPUSH R%d\nMOV R%d, 8\nPUSH R%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nBRKP\n",r,r,r,r,r,r,r,s,r,r,r,r);
	freeReg();
	//fprintf(targetFile,"POP R1\n");
	return s;
}
int printInit(FILE* targetFile){
	int s=getReg();
	int r=getReg();
	fprintf(targetFile,"MOV R%d, \"init\"\nPUSH R%d\nMOV R%d, 8\nPUSH R%d\nPUSH R%d\nPUSH R%d\nPUSH R%d\nCALL 0\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nPOP R%d\nBRKP\n",r,r,r,r,r,r,r,s,r,r,r,r);
	freeReg();
	return s;
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

int getVarAddrForClassDotType(FILE* fp,struct tnode*root){
	int r,s,t1;
	struct Fieldlist* f;
	if(root->nodetype==tCLASSOBJ){
		r=getReg();
		s=root->Gentry->binding;
		fprintf(fp,"MOV R%d, %d\n",r,s);
		fprintf(fp,"MOV R%d,[R%d]\n",r,r);
		return r;
	}
	else if(root->nodetype==tCLASSFIELD){
		f=root->Gentry->Ctype->memberfield;
		while(f!=NULL){
			if(strcmp(f->name,root->varname)==0){
				r=getReg();
				fprintf(fp,"MOV R%d, %d\n",r,f->fieldIndex);
				return r;
			}
			f=f->next;
		}
		printf("error12\n");
		exit(0);
	}
	else if(root->nodetype==tCLASSFIELD2){
		f=root->Ctype->memberfield;
		while(f!=NULL){
			if(strcmp(f->name,root->varname)==0){
				r=getReg();
				fprintf(fp,"MOV R%d, %d\n",r,f->fieldIndex);
				return r;
			}
			f=f->next;
		}
		printf("error12\n");
		exit(0);
	}
	else if(root->nodetype==tSELF){
		r=getReg();
		t1=Llookup("self")->binding;
		fprintf(fp,"MOV R%d,%d\n",r,t1);
		fprintf(fp,"ADD R%d,BP\n",r);
		fprintf(fp,"MOV R%d,[R%d]\n",r,r);
		return r;
	}
	else if(root->nodetype==tCLASSDOT){
		//printf("------------>%d\n",root->left->nodetype);
		int l=getVarAddrForClassDotType(fp,root->left);
		int r=getVarAddrForClassDotType(fp,root->right);
		fprintf(fp,"ADD R%d,R%d\n",l,r);
		return l;
	}
	else{
		printf("ERRROR\n");
		exit(0);
	}
}


int getVarAddrForDotType(FILE* fp,struct tnode*root){
	if(root->nodetype==tTYPEFIELD){
		int r=getReg();
		int s=0;
		if(root->Lentry){
			s=root->Lentry->binding;
			fprintf(fp,"MOV R%d, %d\n",r,s);
			fprintf(fp,"ADD R%d, BP\n",r);
		}else {
			s=root->Gentry->binding;
			fprintf(fp,"MOV R%d, %d\n",r,s);
		}
		fprintf(fp,"MOV R%d,[R%d]\n",r,r);
		return r;
	}
	else if(root->nodetype==tFIELD){
		struct Fieldlist* f;
		f=root->type->fields;
		while(f!=NULL){
			if(strcmp(f->name,root->varname)==0){
				int r=getReg();
				fprintf(fp,"MOV R%d, %d\n",r,f->fieldIndex);
				return r;
			}
			f=f->next;
		}
		printf("error12\n");
		exit(0);
	}
	else if(root->nodetype==tDOT){
		int l=getVarAddrForDotType(fp,root->left);
		int r=getVarAddrForDotType(fp,root->right);
		fprintf(fp,"ADD R%d,R%d\n",l,r);
		return l;
	}
	else if(root->nodetype==tCLASSDOT){
		//printf("------------>%d\n",root->left->nodetype);
		int l=getVarAddrForClassDotType(fp,root->left);
		int r=getVarAddrForClassDotType(fp,root->right);
		fprintf(fp,"ADD R%d,R%d\n",l,r);
		fprintf(fp,"MOV R%d,[R%d]\n",l,l);
		return l;
	}
	else{
		printf("ERRROR2\n");
		exit(0);
	}
}

int getVarAddr(FILE* fp,struct tnode*root){
	char* varName=root->varname;
	int varAddr;
	int s;
	if(root->val>-1){ //array
		varAddr=root->Gentry->binding+ root->val;
	}else{
		s=getReg();
		if(root->Lentry){
			varAddr = root->Lentry->binding;
			fprintf(fp,"MOV R%d, %d\n",s,varAddr);
			fprintf(fp,"ADD R%d, BP\n",s);
		}
		else{
			varAddr = root->Gentry->binding;
			fprintf(fp,"MOV R%d, %d\n",s,varAddr);		
		}
	}
	return s;
}

int codeGen(FILE* fp, struct tnode* root){
	int r,s,funcPos,t1,regcount[20],regptr=-1,sourceReg,destReg,varAddr,label_1,label_2,label_3;
	char* varName;
	char* string;
	struct Lsymbol* ptr;
	struct Gsymbol* tmp;
	struct Typetable* t;
	struct Fieldlist* f;
	struct tnode* node;
	int argArray[25];
	int argArrayInd=-1;
	struct Memberfunclist * mf1,*mf2;
	struct Classtable* ctype1,*c1,*c2;
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
						//printf("%s\n",tmp->name);
						tmp=tmp->next;
					}
					//printf("Q\n");
					if(tmp==NULL){
						//class fn
						c1=root->Ctype;
						printf("class name: %s\n",c1->name);
						if(c1==NULL){
							printf("Code error\n");
							exit(0);
						}
						mf1=c1->Vfuncptr;
						if(mf1==NULL){
							printf("Code error\n");
							exit(0);
						}
						while(mf1!=NULL){
							//printf("%s %s\n",mf1->name,root->varname);
							if(strcmp(mf1->name,root->varname)==0){
								break;
							}
							mf1=mf1->next;
						}
						if(mf1==NULL){
							printf("Code error2\n");
							exit(0);
						}
						fprintf(fp,"L%d:\n",mf1->Flabel);
					}else{
						fprintf(fp,"L%d:\n",tmp->flabel);
					}
				}
				fprintf(fp,"PUSH BP\n");
				fprintf(fp,"MOV BP,SP\n");
				ptr=Lsymbolroot;
				
				//reserve space for local variables NOT for arguments
				while(ptr!=NULL){
					if(ptr->binding>0)
						fprintf(fp,"PUSH R0\n");
					ptr=ptr->next;
				}
				if(root->left!=NULL){
					codeGen(fp,root->left);	
				}
				codeGen(fp,root->right);
				freeAllReg();
				return -1;
		case tRET:
				if(root->val!=tMAINLabel && root->left!=NULL){	//not void return also
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
						fprintf(fp,"POP R16\n");
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
				argArrayInd=-1;
				
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
				
				//push address of self ---> junk value as this is not a fn of a class
				r=getReg();
				fprintf(fp,"PUSH R0\n");
				fprintf(fp,"PUSH R0\n");

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
				fprintf(fp,"POP R16\n");
				//pop out args from stack
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"POP R16\n");
				}

				//pop out self args
				t1=getReg();
				fprintf(fp,"POP R%d\n",t1);
				fprintf(fp,"POP R%d\n",t1);
				freeReg();
				
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
					}else if(root->left->nodetype==tCLASSDOT){
						sourceReg=codeGen(fp,root->left->left);	//contains base address
						destReg=codeGen(fp,root->left->right);	//contains field index
						fprintf(fp,"ADD R%d,R%d\n",sourceReg,destReg);
						printReadReg(fp,sourceReg);
					}
					else{
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
				//printf("QQQQQQQQQQQQQQQQQQQQQQQqqqq %d\n",r);
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

		case tALLOC:
				r=printAlloc(fp);
				return r;

		case tINIT:
				//printf("\nIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII\n");
				r=printInit(fp);
				return r;
		
		case tDOT:
				sourceReg=codeGen(fp,root->left);	//contains base address
				destReg=codeGen(fp,root->right);	//contains field index
				fprintf(fp,"ADD R%d,R%d\n",sourceReg,destReg);
				fprintf(fp,"MOV R%d,[R%d]\n",destReg,sourceReg);
				return destReg;

		case tTYPEFIELD:
				r=getReg();
				s=0;
				if(root->Lentry){
					s=root->Lentry->binding;
					fprintf(fp,"MOV R%d, %d\n",r,s);
					fprintf(fp,"ADD R%d, BP\n",r);
				}else {
					s=root->Gentry->binding;
					fprintf(fp,"MOV R%d, %d\n",r,s);
				}
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);
				return r;
		case tFIELD:
				
				f=root->type->fields;
				while(f!=NULL){
					if(strcmp(f->name,root->varname)==0){
						r=getReg();
						fprintf(fp,"MOV R%d, %d\n",r,f->fieldIndex);
						return r;
					}
					f=f->next;
				}
				printf("error12\n");
				exit(0);

		case tMETHOD:

				/*

				r=getReg();
				s=getReg();
				fprintf(fp,"MOV R%d,%d\n",r,root->Gentry->binding);
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);
				fprintf(fp,"MOV R%d,%d\n",s,root->val);
				fprintf(fp,"ADD R%d,R%d\n",s,r);

				*/

				//check whether the parent class has this fn else error
				mf2=root->Gentry->Ctype->Vfuncptr;
				while(mf2!=NULL){
					if(strcmp(mf2->name,root->varname)==0){
						funcPos=mf2->Funcposition;
						break;
					}
					mf2=mf2->next;
				}
				if(mf2==NULL){
					//function not defined in parent class
					printf("function not defined in parent class\n");
					exit(0);
				}

				//code of tFUNC
				node=root->left;	//1st arg (can be null also)
				argArrayInd=-1;
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
				
				r=getReg();
				s=getReg();
				fprintf(fp,"MOV R%d,%d\n",r,root->Gentry->binding);		//4110
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);						//1032

				//push address of self
				fprintf(fp,"PUSH R%d\n",r);		//push member pointer=1032
				fprintf(fp,"MOV R%d,%d\n",s,root->Gentry->binding);		//4110
				fprintf(fp,"ADD R%d,%d\n",s,1);							//4111
				fprintf(fp,"MOV R%d,[R%d]\n",s,s);						//4096
				fprintf(fp,"PUSH R%d\n",s);		//push v function table pointer=4096

				//push arguments to fn in reverse order
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"PUSH R%d\n",argArray[j]);
				}
				//push empty space for return value
				fprintf(fp,"PUSH R0\n");

				/*mf1=root->Gentry->Ctype->Vfuncptr;
				while(mf1!=NULL){
					if(strcmp(mf1->name,root->varname)==0){
						break;
					}
					mf1=mf1->next;
				}
				fprintf(fp,"CALL L%d\n",mf1->Flabel);
				*/
				fprintf(fp,"MOV R%d,%d\n",r,funcPos);
				fprintf(fp,"ADD R%d,R%d\n",s,r);	//v func table + funcPos
				fprintf(fp,"MOV R%d,[R%d]\n",s,s);	//s=label
				fprintf(fp,"CALL R%d\n",s);	// s will contain label address after label translation
				/*We need number 
				call L[number]??????*/

				
				//after returning from fn call
				
				sourceReg= getReg();
				//save the result
				fprintf(fp,"MOV R%d,[SP]\n",sourceReg);
				//pop out result space
				fprintf(fp,"POP R16\n");
				//pop out args from stack
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"POP R16\n");
				}
				
				//pop out self args
				t1=getReg();
				fprintf(fp,"POP R%d\n",t1);
				fprintf(fp,"POP R%d\n",t1);
				freeReg();

				//restore machine registers
				for(int j=regcount[regptr]-1;j>=0;j--){
					fprintf(fp,"POP R%d\n",j);
				}
				regptr--;
				//printf("-->%d<--\n",sourceReg);
				return sourceReg;

		case tSELFMETHOD:
				r=getReg();
				s=getReg();
				t1=Llookup("self")->binding;
				fprintf(fp,"MOV R%d,%d\n",s,t1);
				fprintf(fp,"ADD R%d,BP\n",s);
				fprintf(fp,"MOV R%d,[R%d]\n",r,s);

				//code of tFUNC
				node=root->left;	//1st arg (can be null also)
				argArrayInd=-1;
				
				while(node!=NULL){
					sourceReg=codeGen(fp,node);
					//printf("<--%d\n",sourceReg);
					argArray[(++argArrayInd)]=sourceReg;
					node=node->third;	//arg list
				}
				//push registers in use
				++regptr;
				regcount[regptr]=reg;
				for(int j=0;j<regcount[regptr];j++){
					fprintf(fp,"PUSH R%d\n",j);
				}
				
				//push address of self
				fprintf(fp,"PUSH R%d\n",r);
				fprintf(fp,"MOV R%d,%d\n",r,1);		//s=BP-3 ->member pointer
				fprintf(fp,"ADD R%d,R%d\n",s,r);	//s=BP-2 ->v func pointer
				fprintf(fp,"MOV R%d,[R%d]\n",s,s);	//s=[BP-2]=4096
				fprintf(fp,"PUSH R%d\n",s);

				//push arguments to fn in reverse order
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"PUSH R%d\n",argArray[j]);
				}
				//push empty space for return value
				fprintf(fp,"PUSH R0\n");

				/*mf1=root->Ctype->Vfuncptr;
				while(mf1!=NULL){
					if(strcmp(mf1->name,root->varname)==0){
						break;
					}
					mf1=mf1->next;
				}
				fprintf(fp,"CALL L%d\n",mf1->Flabel);
				*/
				
				mf2=root->Ctype->Vfuncptr;
				while(mf2!=NULL){
					if(strcmp(mf2->name,root->varname)==0){
						funcPos=mf2->Funcposition;
						break;
					}
					mf2=mf2->next;
				}
				if(mf2==NULL){
					//function not defined in parent class
					printf("function not defined in parent class2\n");
					exit(0);
				}

				fprintf(fp,"MOV R%d,%d\n",r,funcPos);
				fprintf(fp,"ADD R%d,R%d\n",s,r);	//v func table + funcPos
				fprintf(fp,"MOV R%d,[R%d]\n",s,s);	//s=label
				fprintf(fp,"CALL R%d\n",s);	// s will contain label address after label translation

				//after returning from fn call
				
				sourceReg= getReg();
				//save the result
				fprintf(fp,"MOV R%d,[SP]\n",sourceReg);
				//pop out result space
				fprintf(fp,"POP R16\n");
				//pop out args from stack
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"POP R16\n");
				}
				
				//pop out self arg
				t1=getReg();
				fprintf(fp,"POP R%d\n",t1);
				fprintf(fp,"POP R%d\n",t1);
				freeReg();

				//restore machine registers
				for(int j=regcount[regptr]-1;j>=0;j--){
					fprintf(fp,"POP R%d\n",j);
				}
				regptr--;
				//printf("-->%d\n",sourceReg);
				return sourceReg;

		case tSELFMETHOD2:
				r=getReg();
				t1=Llookup("self")->binding;
				fprintf(fp,"MOV R%d,%d\n",r,t1);
				fprintf(fp,"ADD R%d,BP\n",r);
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);
				f=root->Ctype->memberfield;
				while(f!=NULL){
					if(strcmp(f->name,root->right->varname)==0){
						break;
					}
					f=f->next;
				}
				ctype1=f->Ctype;
				s=getReg();
				fprintf(fp,"MOV R%d,%d\n",s,f->fieldIndex);
				fprintf(fp,"ADD R%d,R%d\n",r,s);
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);

				//code of tFUNC
				node=root->left;	//1st arg (can be null also)
				argArrayInd=-1;
				
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
				
				//push address of self
				fprintf(fp,"PUSH R%d\n",r);

				//push arguments to fn in reverse order
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"PUSH R%d\n",argArray[j]);
				}
				//push empty space for return value
				fprintf(fp,"PUSH R0\n");
				mf1=ctype1->Vfuncptr;
				while(mf1!=NULL){
					if(strcmp(mf1->name,root->varname)==0){
						break;
					}
					mf1=mf1->next;
				}
				fprintf(fp,"CALL L%d\n",mf1->Flabel);
				
				//after returning from fn call
				
				sourceReg= getReg();
				//save the result
				fprintf(fp,"MOV R%d,[SP]\n",sourceReg);
				//pop out result space
				fprintf(fp,"POP R16\n");
				//pop out args from stack
				for(int j=argArrayInd;j>=0;j--){
					fprintf(fp,"POP R16\n");
				}
				//pop out self arg
				t1=getReg();
				fprintf(fp,"POP R%d\n",t1);
				freeReg();
				//restore machine registers
				for(int j=regcount[regptr]-1;j>=0;j--){
					fprintf(fp,"POP R%d\n",j);
				}
				regptr--;
				return sourceReg;

		case tCLASSDOT:
				sourceReg=codeGen(fp,root->left);	//contains base address
				destReg=codeGen(fp,root->right);	//contains field index
				fprintf(fp,"ADD R%d,R%d\n",sourceReg,destReg);
				fprintf(fp,"MOV R%d,[R%d]\n",destReg,sourceReg);
				return destReg;

		case tCLASSOBJ:
				r=getReg();
				s=root->Gentry->binding;
				fprintf(fp,"MOV R%d, %d\n",r,s);
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);
				return r;
		
		case tCLASSFIELD:
				f=root->Gentry->Ctype->memberfield;
				while(f!=NULL){
					if(strcmp(f->name,root->varname)==0){
						r=getReg();
						fprintf(fp,"MOV R%d, %d\n",r,f->fieldIndex);
						return r;
					}
					f=f->next;
				}
				printf("error12\n");
				exit(0);

		case tSELF:
				r=getReg();
				t1=Llookup("self")->binding;
				fprintf(fp,"MOV R%d,%d\n",r,t1);
				fprintf(fp,"ADD R%d,BP\n",r);
				fprintf(fp,"MOV R%d,[R%d]\n",r,r);
				return r;
		
		case tCLASSFIELD2:
				f=root->Ctype->memberfield;
				while(f!=NULL){
					if(strcmp(f->name,root->varname)==0){
						r=getReg();
						fprintf(fp,"MOV R%d, %d\n",r,f->fieldIndex);
						return r;
					}
					f=f->next;
				}
				printf("error12\n");
				exit(0);

		case tSTR:
				r=getReg();
				fprintf(fp,"MOV R%d,%s\n",r,root->varname);
				return r;

		case tWRITE:	
				r=codeGen(fp,root->left);
				printWrite(fp,r);
				freeAllReg();
				return -1;
		case tASSIGN:
				//printf("ASSIGN\n");
				if(root->right && root->right->Gentry && root->right->Gentry->Ctype!=NULL && root->left && root->left->Gentry && root->left->Gentry->Ctype!=NULL){
					//do SEMANTIC CHECKING
					c1=Clookup(root->left->Gentry->Ctype->name);
					c2=Clookup(root->right->Gentry->Ctype->name);
					while(c1!=c2 && c2!=NULL){
						c2=c2->Parentptr;
					}
					if(c2==NULL){
						printf("RHS is not a child class of LHS class\n");
						exit(0);
					}
					sourceReg=getVarAddr(fp,root->left);
					destReg=getVarAddr(fp,root->right);
					t1=getReg();
					fprintf(fp,"MOV [R%d],[R%d]\n",sourceReg,destReg);
					fprintf(fp,"MOV R%d,1\n",t1);
					fprintf(fp,"ADD R%d,R%d\n",sourceReg,t1);
					fprintf(fp,"ADD R%d,R%d\n",destReg,t1);
					fprintf(fp,"MOV [R%d],[R%d]\n",sourceReg,destReg);
				}
				else if(root->left->nodetype!=tARRAY){
					if(root->left->nodetype!=tDOT && root->left->nodetype!=tCLASSDOT)
						sourceReg=getVarAddr(fp,root->left);
					else if(root->left->nodetype==tCLASSDOT){
						sourceReg=getVarAddrForClassDotType(fp,root->left);
					}
					else{
						sourceReg=getVarAddrForDotType(fp,root->left);
					}


					if(root->right->type!=typelookup("str")){

						if(root->right->nodetype==tNEW){
							destReg=printAlloc(fp);
							fprintf(fp,"MOV [R%d],R%d\n",sourceReg,destReg);
							r=getReg();
							fprintf(fp,"MOV R%d,1\n",r);
							fprintf(fp,"ADD R%d,R%d\n",sourceReg,r);
							s=4096+classIndex(root->right->varname)*8;
							printf("s=%d\n",s);
							fprintf(fp,"MOV R%d,%d\n",r,s);
							fprintf(fp,"MOV [R%d],R%d\n",sourceReg,r);
						}else{
							destReg=codeGen(fp,root->right);
							//printf("%d\n",destReg);
							fprintf(fp,"MOV [R%d],R%d\n",sourceReg,destReg);	
						}
					}else{
						string=root->right->varname;
						//printf("zz---->%c\n",*(string+0));
						if(*(string+0)=='"'){
							//printf("--------->STRING\n");
							fprintf(fp,"MOV [R%d],%s\n",sourceReg,string);
						}else{
							//a variable contians string
							r=getReg();
							if(root->right->Lentry){
								s=root->right->Lentry->binding;
								fprintf(fp,"MOV R%d, %d\n",r,s);
								fprintf(fp,"ADD R%d, BP\n",r);
								fprintf(fp,"MOV [R%d],[R%d]\n",sourceReg,r);
							}else {
								s=root->Gentry->binding;
								fprintf(fp,"MOV R%d, %d\n",r,s);
								fprintf(fp,"MOV [R%d],[R%d]\n",sourceReg,r);
							}
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
					if(root->right->type!=typelookup("str")){
						destReg=codeGen(fp,root->right);
						fprintf(fp,"MOV [R%d],R%d\n",sourceReg,destReg);
					}else{
						string=root->right->varname;
						//printf("ZZZZZZ\n");
						//fprintf(fp,"MOV [R%d],%s\n",sourceReg,string);
						if(*(string+0)=='"'){
							//printf("--------->STRING\n");
							fprintf(fp,"MOV [R%d],%s\n",sourceReg,string);
						}else{
							//a variable contians string
							r=getReg();
							if(root->right->Lentry){
								s=root->right->Lentry->binding;
								fprintf(fp,"MOV R%d, %d\n",r,s);
								fprintf(fp,"ADD R%d, BP\n",r);
								fprintf(fp,"MOV [R%d],[R%d]\n",sourceReg,r);
							}else {
								s=root->Gentry->binding;
								fprintf(fp,"MOV R%d, %d\n",r,s);
								fprintf(fp,"MOV [R%d],[R%d]\n",sourceReg,r);
							}
						}
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













