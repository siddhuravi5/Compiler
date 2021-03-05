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
#define tMAINLabel 100
#define varLoc 4096
#define SPLoc 4121

struct Paramstruct{
char *name;
int type;
struct Paramstruct* next;
};

//global symbol table
struct Gsymbol {
char* name;
int type;
int size;
int binding;
struct Paramstruct *paramlist;
int flabel;
struct Gsymbol *next;
};

struct Lsymbol{
	char*name;
	int type;
	int binding;
	struct Lsymbol* next;
};


typedef struct tnode { 
	int val;	
	int type;	
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
void install(char *name, int type, int size); 
void symboltype(struct tnode* Type,struct tnode*Varlist);
void printExit(FILE* targetFile);
int getLabel();
int getReg();
void freeReg();
void printRead(FILE* targetFile, int varAddr);
void printWrite(FILE* targetFile, int regNum);
int getVarAddr(FILE* fp,struct tnode*root);
int codeGen(FILE* fp, struct tnode* root);
struct Paramstruct* createParam(char* name,int size);
struct Paramstruct* addParam(struct Paramstruct* root,struct Paramstruct* elt);
void Ginstall(char* name,int type,int size,int binding,struct Paramstruct* paramlist,int flabel);
void updateTypeToGsymbol(int type);
void printGsymbolTable();
void Linstall(char* name, int type);
void Linstallbylist(struct Paramstruct* root);
void Linstallbylistwithtype(struct Paramstruct* root, int type);
struct Lsymbol* Llookup(char* name);
struct Gsymbol* Glookup(char* name);
struct tnode* appendArgList(struct tnode* root, struct tnode* elt);
void Lprint();
void reset_fnargumentsbinding();

/*Create a node tnode*/
struct tnode* createTree(int val, int type, char* c, int nodeType,struct Lsymbol* Lsym,struct Gsymbol* Gsym, struct tnode *l, struct tnode *r,struct tnode *third);

struct Gsymbol* Gsymbolroot;
struct Lsymbol* Lsymbolroot;
