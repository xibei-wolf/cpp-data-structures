#pragma once
typedef int ELEMENT;

typedef struct AVLNode{
	ELEMENT val;
	struct AVLNode* lchild;
	struct AVLNode* rchild;
	int height;
}AVLNode;

typedef struct AVLTree {
	AVLNode* root;
}AVLTree;

/*  ·ÇµÝ¹é
typedef struct AVLNode {
	ELEMENT val;
	struct AVLNode* lchild;
	struct AVLNode* rchild;
	struct AVLNode* parent;
	int height;
}AVLNode;
*/

AVLNode* BuyAVLNode();
int Get_Height(AVLNode* node);
void Fresh_height(AVLNode* node);
int Get_BalanceFactor(AVLNode* node);

AVLNode* L_Rotate(AVLNode* node);
AVLNode* R_Rotate(AVLNode* node);
AVLNode* Rotate(AVLNode* node);

void Init_AVL(AVLTree* pTree);
bool Delet_AVL(AVLTree* pTree, ELEMENT val);
AVLNode* Delet_Help(AVLNode* root, ELEMENT val);
bool Insert_AVL(AVLTree* pTree, ELEMENT val);
AVLNode* Insert_Help(AVLNode* root, ELEMENT val);
AVLNode* Search_AVL(AVLTree* pTree,ELEMENT val);
void show_inOrder1(AVLNode* node);
void show_inOrder2(AVLTree* pTree);



