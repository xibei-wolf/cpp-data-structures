#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stack>
#include<queue>
#include"BSTree.h"

void Init(BSTree* pTree) {
	assert(pTree != NULL);
	if (pTree == NULL)
		exit(EXIT_FAILURE);
	pTree->root = NULL;
}
BSTNode* buynode() {
	BSTNode* p = (BSTNode*)malloc(sizeof(BSTNode));
	if (p == NULL)
		exit(EXIT_FAILURE);
	memset(p, 0, sizeof(BSTNode));
	return p;
}
bool Insert_BSTree(BSTree* pTree, ELEMENT val)
{
	assert(pTree != NULL);
	if (pTree == NULL)
		exit(EXIT_FAILURE);
	BSTNode* p = pTree->root;
	BSTNode* pp = NULL;
	if (p == NULL) {
		BSTNode* pnew = buynode();
		pnew->val = val;
		pTree->root = pnew;
		return true;
	}
	while (p!=NULL&&p->val!=val)
	{
		pp = p;
		p = p->val > val ? p->lchild : p->rchild;
	}
	if (p!=NULL)
		return false;

	BSTNode* pnew = buynode();
	pnew->val = val;
	pnew->parent = pp;
	if (pp->val > val) {
		pp->lchild = pnew;
	}
	else {
		pp->rchild = pnew;
	}
	
	return true;
}
BSTNode* FInd_Post(BSTNode* boot) {
	BSTNode* p = boot;
	BSTNode* pp = boot->parent;
	if(p->rchild != NULL)
	{
		return Get_Min(p->rchild);
	}
	while (pp!=NULL&&pp->val<p->val)
	{
		pp = pp->parent;
	}
	return pp;
}
BSTNode* FInd_Pre(BSTNode* boot) {
	BSTNode* p = boot;
	BSTNode* pp = boot->parent;
	if (p->lchild != NULL)
	{
		return Get_Max(p->lchild);
	}
	while (pp != NULL && pp->val > p->val)
	{
		pp = pp->parent;
	}
	return pp;
}
BSTNode* Get_Min(BSTNode* boot) {
	BSTNode* p = boot;
	while (p != NULL&&p->lchild!=NULL)
	{
		p = p->lchild;
	}
	return p;
}
BSTNode* Get_Max(BSTNode* boot) {
	BSTNode* p = boot;
	while (p != NULL&&p->rchild!=NULL)
	{
		p = p->rchild;
	}
	return p;
}
bool Delete_BSTree(BSTree* pTree, ELEMENT val) {
	assert(pTree != NULL);
	if (pTree == NULL)
		exit(EXIT_FAILURE);
	BSTNode* p = Search_BSTree(pTree, val);
	
	if (p == NULL) {
		return true;
	}
	if (p->lchild != NULL&&p->rchild != NULL) {
		BSTNode* tmp = FInd_Post(p); 
		p->val = tmp->val;
		p = tmp;
	}
	BSTNode* father = p->parent;
	BSTNode* child = p->lchild != NULL ? p->lchild : p->rchild;
	if (father == NULL) {
		pTree->root = child;		
	}
	else {
		if (father->val > val) 
			 father->lchild = child;
		else father->rchild = child;
	}
	if (child != NULL)child->parent = father;
	free(p);
	return true;
}

BSTNode* Search_BSTree(BSTree* pTree, ELEMENT val) {
	BSTNode* p = pTree->root;
	while (p != NULL && p->val != val)
	{
		p = p->val > val ? p->lchild : p->rchild;
	}
	return p;
}

void show(BSTNode* root){
	if (root == NULL)
		return;
	show(root->lchild);
	printf("%d ", root->val);
	show(root->rchild);
}
/*
int main() {
	BSTree head;
	Init(&head);
	Insert_BSTree(&head, 56);
	Insert_BSTree(&head, 98);
	Insert_BSTree(&head, 23);
	Insert_BSTree(&head, 78);
	Insert_BSTree(&head, 12);
	Insert_BSTree(&head, 67);
	Insert_BSTree(&head, 23);
	Insert_BSTree(&head, 89);
	Insert_BSTree(&head, 34);
	show(head.root);
	putchar('\n');
	Delete_BSTree(&head, 56);
	Delete_BSTree(&head, 67);
	show(head.root);
	
	return 0;
}
*/