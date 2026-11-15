#pragma once
typedef char ELEMENT;
typedef struct Bin_Node {
	ELEMENT val;
	struct Bin_Node* lchild;
	struct Bin_Node* rchild;
}Bin_Node;

typedef struct Three_Node {
	ELEMENT val;
	struct Three_Node* lchild;
	struct Three_Node* parent;
	struct Three_Node* rchild;
}Three_Node;

typedef struct Bin_Tree{
	Bin_Node* root;
	//int cursize;
}Bin_Tree;

void Init(Bin_Tree* pTree);
Bin_Node* BuyNode();
Bin_Node* Create1();
Bin_Node* Create2();
Bin_Node* Create3_Pre_in();
Bin_Node* Create3_post_in();
void Level_traversal(Bin_Node* root);
void S_Level_traversal(Bin_Node* root);
void RS_Level_traversal(Bin_Node* root);
void PreOrder(Bin_Node* root);
void InOrder(Bin_Node* root);
void PostOrder(Bin_Node* root);
void PreOrder_Norecursion(Bin_Tree* pTree);
void InOrder_Norecursion(Bin_Tree* pTree);
void PostOrder_Norecursion(Bin_Tree* pTree);
void PostOrder_Norecursion2(Bin_Tree* pTree);
void Destroy_Norecursion(Bin_Tree* pTree);
void Destroy(Bin_Node* root);

