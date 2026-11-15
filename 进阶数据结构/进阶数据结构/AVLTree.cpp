#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stack>
#include "AVLTree.h"

AVLNode* BuyAVLNode() {
	AVLNode* p = (AVLNode*)malloc(sizeof(AVLNode));
	if (p == NULL)
		exit(EXIT_FAILURE);
	memset(p, 0, sizeof(AVLNode));
	return p;
}

int Get_Height(AVLNode* node) {
	if (node == NULL)
		return -1;
	return node->height;
}
void Fresh_height(AVLNode* node) {
	if (node == NULL)
		return ;
	int lheight = Get_Height(node->lchild);
	int rheight = Get_Height(node->rchild);
	node->height= lheight > rheight ? lheight+1 : rheight+1;
}
int Get_BalanceFactor(AVLNode* node) {
	if (node == NULL)
		return 0;
	return Get_Height(node->lchild) - Get_Height(node->rchild);
}



AVLNode* L_Rotate(AVLNode* node) {
	AVLNode* child = node->rchild;
	AVLNode* grandchild = child->lchild;
	node->rchild = grandchild;
	child->lchild = node;
	Fresh_height(node);
	Fresh_height(child);
	return child;
}


AVLNode* R_Rotate(AVLNode* node) {
	AVLNode* child = node->lchild;
	AVLNode* grandchild = child->rchild;
	node->lchild = grandchild;
	child->rchild = node;
	Fresh_height(node);
	Fresh_height(child);
	return child;
}
AVLNode* Rotate(AVLNode* node) {
	int factor = Get_BalanceFactor(node);
	if (factor == 2) {
		int child_factor = Get_BalanceFactor(node->lchild);
		if(child_factor==1||child_factor==0)
			return R_Rotate(node);
		else {
			node->lchild = L_Rotate(node->lchild);
			return R_Rotate(node);
		}
	}
	if(factor==-2){
		int child_factor = Get_BalanceFactor(node->rchild);
		if (child_factor == -1 || child_factor == 0)
			return L_Rotate(node);
		else {
			node->rchild = R_Rotate(node->rchild);
			return L_Rotate(node);
		}
	}
	return node;
}





void Init_AVL(AVLTree* pTree) {
	assert(pTree != NULL);
	if (pTree == NULL)exit(EXIT_FAILURE);
	pTree->root = NULL;
}
bool Insert_AVL(AVLTree* pTree, ELEMENT val) {
	pTree->root=Insert_Help(pTree->root, val);
	return true;
}
AVLNode* Insert_Help(AVLNode* root, ELEMENT val) {
	if (root == NULL) {
		AVLNode* pnew = BuyAVLNode();
		pnew->val = val;
		return pnew;
	}
	if (root->val > val)
		root->lchild = Insert_Help(root->lchild, val);
	else if (root->val < val)
		root->rchild = Insert_Help(root->rchild, val);
	else return root;
	Fresh_height(root);
	root=Rotate(root);
	return root;
}

bool Delet_AVL(AVLTree* pTree, ELEMENT val) {
	pTree->root = Delet_Help(pTree->root, val);
	return true;
}

AVLNode* Delet_Help(AVLNode* root, ELEMENT val) {
	if (root == NULL)
		return NULL;
	if (root->val == val) {
		if (root->lchild==NULL||root->rchild==NULL) {
			AVLNode* child= root->lchild != NULL ? root->lchild : root->rchild;
			free(root);
			return child;
		}
		else if(root->lchild!=NULL&&root->rchild!=NULL){
			AVLNode* prenode = root->rchild;
			while (prenode->lchild!=NULL)
			{
				prenode = prenode->lchild;
			}
			int cat = prenode->val;
			root->val = cat;
			Delet_Help(root->rchild,cat);
		}

	}
	else if (root->val > val)
		root->lchild = Delet_Help(root->lchild, val);
	else
		root->rchild  = Delet_Help(root->rchild, val);
	Fresh_height(root);
	root = Rotate(root); 
	return root;
}



AVLNode* Search_AVL(AVLTree* pTree, ELEMENT val) {
	AVLNode* p = pTree->root;
	while (p!=NULL&&p->val!=val)
	{
		p = p->val > val ? p->lchild : p->rchild;
	}
	return p;
}

void show_inOrder1(AVLNode* node) {
	if (node == NULL)
		return;
	show_inOrder1(node->lchild);
	printf("%d ", node->val);
	show_inOrder1(node->rchild);
}
void show_inOrder2(AVLTree* pTree) {
	assert(pTree != NULL);
	if (pTree == NULL) exit(EXIT_FAILURE);
	std::stack<AVLNode*> st;
	if(pTree->root!=NULL)
		st.push(pTree->root);
	bool tag = true;
	while (!st.empty())
	{
		
		while (tag && st.top()->lchild != NULL) {
			st.push(st.top()->lchild);
		}
		AVLNode* p = st.top();
		printf("%d ", p->val);
		st.pop();
		tag = false;
		if (p->rchild != NULL) {
			st.push(p->rchild);
			tag = true;
		}
	}
}



/*
int main() {
	AVLTree tree;
	Init_AVL(&tree);
	Insert_AVL(&tree, 14);
	Insert_AVL(&tree, 9);
	Insert_AVL(&tree, 5);
	Insert_AVL(&tree, 17);
	Insert_AVL(&tree, 11);
	Insert_AVL(&tree, 12);
	Insert_AVL(&tree, 17);
	Insert_AVL(&tree, 19);
	Insert_AVL(&tree, 16);
	Insert_AVL(&tree, 27);
	Delet_AVL(&tree, 5);
	show_inOrder2(&tree);
	return 0;
}
*/