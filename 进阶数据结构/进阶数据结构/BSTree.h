#pragma once
typedef int ELEMENT;
typedef struct BSTNode {
	ELEMENT val;
	struct BSTNode* lchild;
	struct BSTNode* rchild;
	struct BSTNode* parent;
}BSTNode;
typedef struct BSTree {
	BSTNode* root;
}BSTree;
void Init(BSTree *pTree);
BSTNode* buynode();
bool Insert_BSTree(BSTree* pTree, ELEMENT val);
bool Delete_BSTree(BSTree* pTree, ELEMENT val);
BSTNode* Search_BSTree(BSTree* pTree, ELEMENT val);
void show(BSTNode* root);

BSTNode* FInd_Post(BSTNode* boot, ELEMENT val);
BSTNode* FInd_Pre(BSTNode* boot, ELEMENT val);
BSTNode* Get_Min(BSTNode* boot);
BSTNode* Get_Max(BSTNode* boot);
