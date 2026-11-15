#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include "BTree.h"

BTNode* BuyNode() {
	BTNode* pnewnode=(BTNode*)malloc(sizeof(BTNode));
	if (pnewnode == NULL) exit(1);
	memset(pnewnode, 0, sizeof(BTNode));
	return pnewnode;
}
Result* BuyRes() {

	Result* res = (Result*)malloc(sizeof(Result));
	if (res == NULL) exit(1);
	memset(res, 0, sizeof(Result));
	return res;
}

void Init_BTree(BTree* pTree) {
	assert(pTree != NULL);
	if (pTree == NULL)exit(EXIT_FAILURE);
	pTree->root = NULL;
}
//2.插入
void Insert_Split_Adjust(BTree* ptree, BTNode* node) {
	assert(ptree != NULL);
	if (ptree == NULL)exit(EXIT_FAILURE);
	BTNode* pnew = BuyNode();
	int i = 1;
	int j = M / 2+1;
	int fkey = node->key_arr[j];
	
	while (i<j)
	{
		pnew->key_arr[i] = node->key_arr[j+i];
		i++;

	}
	if (node->ptr_arr[0] != NULL) {
		for (int i = 0;i < j;i++) {
			pnew->ptr_arr[i] = node->ptr_arr[i + j];
			node->ptr_arr[j + i]->parent = pnew;
		}
	}
	node->key_num = M / 2;
	pnew->key_num = M / 2;

	if (node->parent==NULL) {
		BTNode* father = BuyNode();
		father->key_arr[1] = fkey;
		father->key_num++;
		node->parent = father;
		pnew->parent = father;
		ptree->root = father;
		father->ptr_arr[0] = node;
		father->ptr_arr[1] = pnew;
		return;
	}
	else {
		BTNode* father = node->parent;
		int k;
		for (k = father->key_num;k > 0;k--) {
			if (father->key_arr[k] > fkey){
				father->key_arr[k + 1] = father->key_arr[k];
				father->ptr_arr[k + 1] = father->ptr_arr[k];
			}else break;
		}
		father->key_arr[k + 1] = fkey;
		father->ptr_arr[k + 1] = pnew;
		node->parent = father;
		pnew->parent = father;
		father->key_num++;
		if (father->key_num == M) {
			Insert_Split_Adjust(ptree, father);
		}
	}
}


bool Insert_BTree(BTree* pTree, ELEMTYPE key) {
	assert(pTree != NULL);
	if (pTree == NULL) exit(EXIT_FAILURE);
	if (pTree->root == NULL) {
		pTree->root = BuyNode();
		pTree->root->key_arr[1] = key;
		pTree->root->key_num++;
		return true;
	}
	Result* res = Search_end_BTree(pTree, key);
	if (res->tag) return true;
	BTNode* loc = res->pNode;
	int i = loc->key_num;
	while (i>=res->index)
	{
		loc->key_arr[i+1] = loc->key_arr[i];
		i--;
	}
	loc->key_arr[res->index] = key;
	loc->key_num++;

	if (loc->key_num == M) {
		Insert_Split_Adjust(pTree, loc);
	}
	return true;
}
//3.删除
bool Delet_BTree(BTree* pTree, ELEMTYPE key) {
	return true;
}

//4.查找 返回整个节点
BTNode* Search_BTree(BTree* pTree, ELEMTYPE key) {
	assert(pTree!= NULL);
	if (pTree == NULL)exit(EXIT_FAILURE);
	BTNode* node = pTree->root;
	while (node)
	{
		int i = 1;
		while (node->key_arr[i]<key&&i<=node->key_num)
		{
			i++;
		}
		if (node->key_arr[i] == key) return node;
		else node = node->ptr_arr[i-1];
	}
	return NULL;
}
//5.查找 返回具体位置或者插入位置
Result* Search_end_BTree(BTree* pTree, ELEMTYPE key) {
	assert(pTree != NULL);
	if (pTree == NULL)exit(EXIT_FAILURE);
	BTNode* node = pTree->root;
	BTNode* pnode = NULL;
	Result* res = BuyRes();
	int i=1;
	while (node)
	{
		pnode = node;
		i = 1;
		while (i <= node->key_num && node->key_arr[i] < key) i++;
		if (i<= node->key_num && node->key_arr[i] == key) {
			res->index = i;
			res->pNode = node;
			res->tag = true;
			return res;
		}
		else node = node->ptr_arr[i - 1];	
	}
	res->tag = false;
	res->index = i;
	res->pNode = pnode;
	return res;
}

//5.打印(中序遍历，顺序遍历)
void show_BTree(BTNode* root) {
	if (root == NULL) return;
	int i = 0;
	for (i = 0;i < root->key_num;i++) {
		if (root->ptr_arr[i] != NULL) {
			show_BTree(root->ptr_arr[i]);
		}
		printf("%d ", root->key_arr[i + 1]);
	}
	show_BTree(root->ptr_arr[root->key_num]);
	return;
}

int main() {
	BTree head;
	Init_BTree(&head);
	Insert_BTree(&head, 1);
	Insert_BTree(&head, 5);
	Insert_BTree(&head, 7);
	Insert_BTree(&head, 4);
	Insert_BTree(&head, 16);
	Insert_BTree(&head, 35);
	Insert_BTree(&head, 24);
	Insert_BTree(&head, 42);
	Insert_BTree(&head, 21);
	Insert_BTree(&head, 17);
	Insert_BTree(&head, 18);
	show_BTree(head.root);
	return 0;
}