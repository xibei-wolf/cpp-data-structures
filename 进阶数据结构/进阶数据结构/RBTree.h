#define _CRT_SECURE_NO_WARNINGS 

typedef int ELEMENT;

typedef enum{RED,BLACK} TYPE_COLOR;

typedef struct RBNode {
	ELEMENT val;
	struct RBNode* lchild;
	struct RBNode* parent;
	struct RBNode* rchild;
	TYPE_COLOR color;
}RBNode;

typedef struct RBTree {
	RBNode* root;
}RBTree;

RBNode* BuyRBNode();
RBNode* L_Rotate(RBNode* node);
RBNode* R_Rotate(RBNode* node);

void Insert(RBTree* tree, RBNode* node);
void Delet(RBTree* tree, RBNode* node, bool tag);

void RB_Init(RBTree* tree);
bool RB_Insert(RBTree* tree, ELEMENT val);
bool RB_Delet(RBTree* tree, ELEMENT val);
RBNode* RB_Search(RBTree* tree, ELEMENT val);
void show(RBNode* node);
void show(RBTree* Tree);