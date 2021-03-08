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
#define tCLASSOBJ 35
#define tFREE 36
#define tCLASSFIELD 37
#define tCLASSFIELD2 38
#define tCLASSDOT 39
#define tSELFMETHOD2 40
#define tSELFMETHOD 41
#define tSELF 42
#define tMETHOD 43
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
	struct Classtable *Ctype;
	struct Fieldlist* next;
};

struct Memberfunclist {
 	char *name;                      
	struct Typetable *type;         
	struct Paramstruct *paramlist;   
	int Funcposition; 
 	int Flabel;                      
	struct Memberfunclist *next;     
};

struct Typetable{
	char* name;
	int size;
	struct Fieldlist *fields;
	struct Typetable *next;
};


struct Classtable {
 	char *name;              
	struct Fieldlist *memberfield;      
	struct Memberfunclist *Vfuncptr; 
	struct Classtable *Parentptr;         
	int Class_index;                    
	int Fieldcount;
  	int Methodcount;        
	struct Classtable *next;
};

//global symbol table
struct Gsymbol {
	char* name;
	struct Typetable* type;
	struct Classtable *Ctype;
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
	struct Classtable *Ctype;	
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
void updateTypeToGsymbol(char* type);
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
void ClassFinstall(char *name1,char* name2);
struct Typetable* typelookuponly(char* name);
struct Classtable* Clookup(char* name);
void ClassMinstall(struct Typetable* type,char* name,struct Paramstruct* params);
int getBindingForMethod2(char* name1,char* name2);
struct Typetable* findclassmemtype(char* cname,char* type);
/*Create a node tnode*/
struct tnode* createTree(int val, struct Typetable* type, char* c, int nodeType,struct Lsymbol* Lsym,struct Gsymbol* Gsym, struct tnode *l, struct tnode *r,struct tnode *third,struct Classtable* Centry);
void functypecheck(struct Paramstruct* params, struct Gsymbol* fn);
struct Typetable* fieldtype(char* name1,char* name2);
struct Typetable* fieldtypelookup(char* name1,char* name2);
struct Gsymbol* Gsymbolroot;
struct Lsymbol* Lsymbolroot;
struct Classtable* classroot;