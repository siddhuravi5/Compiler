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
#define varLoc 4096
#define SPLoc 4121


typedef struct tnode { 
	int val;	// value of a number for NUM nodes.
	int type;	//type of variable
	char* varname;	//name of a variable for ID nodes  
	int nodetype;  // information about non-leaf nodes - read/write/connector/+/* etc.  
	struct tnode *left,*right;	//left and right branches   
}tnode;
	

/*Make a leaf tnode and set the value of val field*/
struct tnode* makeLeafNode(int n);
	
/*Make a tnode with opertor, left and right branches set*/
struct tnode* makeOperatorNode(char c,struct tnode *l,struct tnode *r);
	
/*To evaluate an expression tree*/
int evaluate(struct tnode *t);

/*Create a node tnode*/
struct tnode* createTree(int val, int type, char* c, int nodeType, struct tnode *l, struct tnode *r);
