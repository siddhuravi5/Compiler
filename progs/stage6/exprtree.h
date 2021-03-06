#define tNUM 0
#define tVAR 1
#define tADD 2
#define tSUB 3
#define tMUL 4
#define tDIV 5
#define tREAD 6
#define tWRITE 7
#define tASSIGN 8
#define tCONNECT 9
#define tINT 10
#define tLT 11
#define tGT 12
#define tLE 13
#define tGE 14
#define tNE 15
#define tEQ 16
#define tBOOL 17
#define tWHILE 18
#define tIF 19
#define tBREAK 20
#define tCONTINUE 21
#define tSTR 22
#define tARRAY 23
#define tMOD 24
#define tFUNC 25
#define tRET 26
#define tFBODY 27
#define tAND 28
#define tOR 29
#define tFIELD 30
#define tTYPEFIELD 31
#define tDOT 32
#define tINIT 33
#define tALLOC 34
#define tFREE 35
#define tMAINLabel 100
#define varLoc 4096
#define SPLoc 4121

struct Paramstruct{
char *name;
struct Typetable* type;
struct Paramstruct* next;
};

struct Fieldlist{
	char *name;
	int fieldIndex;
	struct Typetable*type;
	struct Fieldlist* next;
};

struct Typetable{
	char* name;
	int size;
	struct Fieldlist *fields;
	struct Typetable *next;
};

//global symbol table
struct Gsymbol {
	char* name;
	struct Typetable* type;
	int size;
	int binding;
	struct Paramstruct *paramlist;
	int flabel;
	struct Gsymbol *next;
};

struct Lsymbol{
	char*name;
	struct Typetable* type;
	int binding;
	struct Lsymbol* next;
};


typedef struct tnode { 
	int val;	
	struct Typetable* type;	
	char* varname;	
	int nodetype;  
	struct Lsymbol *Lentry;
	struct Gsymbol *Gentry;
	struct tnode *left,*right,*third;	
}tnode;

struct Gsymbol *lookup(char * name); 

int getSP();
void printSymbolTable();
void updateSizeToLatestId(int size);
void install(char *name, struct Typetable* type, int size); 
void symboltype(struct tnode* Type,struct tnode*Varlist);
void printExit(FILE* targetFile);
int getLabel();
int getReg();
void freeReg();
void printRead(FILE* targetFile, int varAddr);
void printWrite(FILE* targetFile, int regNum);
int getVarAddr(FILE* fp,struct tnode*root);
int codeGen(FILE* fp, struct tnode* root);
struct Paramstruct* createParam(char* name,struct Typetable* type);
struct Paramstruct* addParam(struct Paramstruct* root,struct Paramstruct* elt);
void Ginstall(char* name,struct Typetable* type,int size,int binding,struct Paramstruct* paramlist,int flabel);
void updateTypeToGsymbol(struct Typetable* type);
void printGsymbolTable();
void Linstall(char* name, struct Typetable* type);
void Linstallbylist(struct Paramstruct* root);
void Linstallbylistwithtype(struct Paramstruct* root, struct Typetable* type);
struct Lsymbol* Llookup(char* name);
struct Gsymbol* Glookup(char* name);
struct tnode* appendArgList(struct tnode* root, struct tnode* elt);
void Lprint();
void printTypeTable();
void reset_fnargumentsbinding();
struct Typetable* typelookup(char*name);
void typeinstall(char* name);
void typeinstallwithfields(char* name,int size, struct Fieldlist *fields);
struct Fieldlist* fieldappend(struct Fieldlist* root,struct Fieldlist* elt);
struct Fieldlist* fieldinstall(char *name,struct Typetable* type);
struct Typetable* typesearch(char *name);
/*Create a node tnode*/
struct tnode* createTree(int val, struct Typetable* type, char* c, int nodeType,struct Lsymbol* Lsym,struct Gsymbol* Gsym, struct tnode *l, struct tnode *r,struct tnode *third);
void functypecheck(struct Paramstruct* params, struct Gsymbol* fn);
struct Typetable* fieldtype(char* name1,char* name2);
int getdynamicbinding();
struct Typetable* fieldtypelookup(char* name1,char* name2);
struct Gsymbol* Gsymbolroot;
struct Lsymbol* Lsymbolroot;
