#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include <stack>
#include <string.h>
#include <queue>
#include "Binary.h"
void Init(Bin_Tree* pTree) {
	pTree->root=NULL;
}
Bin_Node* BuyNode() {
	Bin_Node* pnewnode = (Bin_Node*)malloc(sizeof(Bin_Node));
	if (pnewnode == NULL)
		return NULL;
	pnewnode->lchild = pnewnode->rchild = NULL;
	return pnewnode;
}
Bin_Node* Create1() {
	Bin_Node* root = BuyNode();
	root->val = 'A';
	root->lchild = BuyNode();
	root->rchild = BuyNode();
	root->lchild->val = 'B';
	root->rchild->val = 'E';
	root->lchild->lchild= BuyNode();
	root->lchild->rchild= BuyNode();
	root->rchild->lchild= BuyNode();
	root->rchild->rchild= BuyNode();
	root->lchild->lchild->val= 'C';
	root->lchild->rchild->val= 'D';
	root->rchild->lchild->val = 'F';
	root->rchild->rchild->val = 'G';
	return root;
}
Bin_Node* Create2() {
	Bin_Node* root = NULL;
	ELEMENT ch;
	scanf("%c", &ch);
	if (ch != '#') {
		root = BuyNode();
		root->val;
		root->lchild = Create2();
		root->rchild = Create2();
	}
	return root;
}
int Find_Pos(const char* buff,char x) {
	int i = 0;
	while (buff[i] != x) {
		i++;
	}
	return i;
}
Bin_Node* Create3_Pre_in(const char* buff_pre,const char* buff_in,int n) {
	Bin_Node* pnewnode = NULL;
	if (n > 0) {
		pnewnode = BuyNode();
		pnewnode->val = buff_pre[0];
		int index = Find_Pos(buff_in, buff_pre[0]);
		pnewnode->lchild = Create3_Pre_in(buff_pre+1,buff_in,index);
		pnewnode->rchild = Create3_Pre_in(buff_pre+index+1,buff_in+index+1,n-index-1);
	}
	return pnewnode;
}
Bin_Node* Create3_post_in(const char* buff_in, const char* buff_post, int n) {
	Bin_Node* pnewnode = NULL;
	if (n > 0) {
		pnewnode = BuyNode();
		pnewnode->val = buff_post[n-1];
		int index = Find_Pos(buff_in, buff_post[n-1]);
		pnewnode->lchild = Create3_Pre_in(buff_in, buff_post, index);
		pnewnode->rchild = Create3_Pre_in(buff_in + index + 1, buff_post + index, n - index - 1);
	}

	return NULL;
}
void PreOrder(Bin_Node* root) {
	if (root == NULL)
		return;
	printf("%c ", root->val);
	PreOrder(root->lchild);
	PreOrder(root->rchild);
}
void InOrder(Bin_Node* root){
	if (root == NULL)
		return;
	InOrder(root->lchild);
	printf("%c ", root->val);
	InOrder(root->rchild);
}
void PostOrder(Bin_Node* root) {
	if (root == NULL)
		return;
	PostOrder(root->lchild);
	PostOrder(root->rchild);
	printf("%c ", root->val);
}

void PreOrder_Norecursion(Bin_Tree* pTree) {
	std::stack<Bin_Node*> st;
	st.push(pTree->root);
	while (!st.empty())
	{
		Bin_Node* p = st.top();
		printf("%c ", p->val);
		st.pop();
		if (p->rchild != NULL)
			st.push(p->rchild);
		if (p->lchild != NULL)
			st.push(p->lchild);
	}
}
void InOrder_Norecursion(Bin_Tree* pTree) {
	std::stack<Bin_Node*> st;
	st.push(pTree->root);
	bool tag = true;
	while (!st.empty())
	{
		while (tag&&st.top()->lchild!=NULL)
		{
			st.push(st.top()->lchild);
		}
		Bin_Node* p = st.top();
		printf("%c ", p->val);
		st.pop();
		if (p->rchild != NULL) {
			st.push(p->rchild);
			tag = true;
		}
		else {
			tag = false;
		}
	}
}
void PostOrder_Norecursion2(Bin_Tree* pTree) {
	std::stack<Bin_Node*> s1,s2;
	s1.push(pTree->root);
	while (!s1.empty())
	{
		Bin_Node* p = s1.top();
		s1.pop();
		s2.push(p);
		if (p->lchild != NULL) {
			s1.push(p->lchild);
		}
		if (p->rchild != NULL) {
			s1.push(p->rchild);
		}
	}
	while (!s2.empty())
	{
		Bin_Node* q = s2.top();
		printf("%c ", q->val);
		s2.pop();
	}

}
void PostOrder_Norecursion(Bin_Tree* pTree) {
	std::stack<Bin_Node*> st;
	st.push(pTree->root);
	bool tag=true;
	Bin_Node* pnode=NULL;
	while (!st.empty())
	{
		while (tag&&st.top()->lchild!=NULL)
		{
			st.push(st.top()->lchild);
		}

		if (st.top()->rchild != NULL&&st.top()->rchild!=pnode) {
			st.push(st.top()->rchild);
			tag = true;
		}
		else {
			pnode = st.top();
			printf("%c ", pnode->val);
			st.pop();
			tag = false;
		}
	}
}


void Destroy_Norecursion(Bin_Tree* pTree) {
	std::stack<Bin_Node*> st;
	st.push(pTree->root);
	while (!st.empty())
	{
		
		Bin_Node* p = st.top();
		st.pop();
	}
}
void Destroy(Bin_Node* root) {
	if (root == NULL)
		return;
	Destroy(root->lchild);
	Destroy(root->rchild);
	free(root);
}
void Level_traversal(Bin_Node* root) {
	assert(root != NULL);
	if (root == NULL)
		exit(0);
	std::queue<Bin_Node*> qu;
	qu.push(root);
	while (!qu.empty())
	{
		Bin_Node* q = qu.front();
		printf("%c ", q->val);
		qu.pop();
		if (q->lchild != NULL)
			qu.push(q->lchild);
		if (q->rchild != NULL)
			qu.push(q->rchild);
	}
}
void S_Level_traversal(Bin_Node* root) {
	std::stack<Bin_Node*> s1, s2;
	s1.push(root);
	while (!s1.empty()||!s2.empty())
	{
		while (!s1.empty()) {
			Bin_Node* p = s1.top();
			s1.pop();
			printf("%c ", p->val);
			if (p->rchild != NULL)
				s2.push(p->rchild);
			if (p->lchild != NULL)
				s2.push(p->lchild);
		}
		while(!s2.empty()) {
			Bin_Node* p = s2.top();
			s2.pop();
			printf("%c ", p->val);
			if (p->lchild != NULL)
				s1.push(p->lchild);
			if (p->rchild != NULL)
				s1.push(p->rchild);
		}
	}
}
void RS_Level_traversal(Bin_Node* root) {
	std::stack<Bin_Node*> s1, s2;
	s1.push(root);
	while (!s1.empty() || !s2.empty())
	{
		while (!s1.empty()) {
			Bin_Node* p = s1.top();
			s1.pop();
			printf("%c ", p->val);
			if (p->lchild != NULL)
				s2.push(p->lchild);
			if (p->rchild != NULL)
				s2.push(p->rchild);
		}
		while (!s2.empty()) {
			Bin_Node* p = s2.top();
			s2.pop();
			printf("%c ", p->val);
			if (p->rchild != NULL)
				s1.push(p->rchild);
			if (p->lchild != NULL)
				s1.push(p->lchild);
		}
	}
}
/*
int main() {
	Bin_Tree head;
	Init(&head);
	const char* buff_pre="ABCDEFGH";
	const char* buff_in="CBEDFAGH";
	const char* buff_post = "CEFDBHGA";
	int len = strlen(buff_pre);
	head.root=Create3_Pre_in(buff_pre,buff_in,len);
	//head.root = Create3_post_in(buff_in, buff_post, len);
	PreOrder(head.root);
	putchar('\n');
	PreOrder_Norecursion(&head);
	putchar('\n');
	InOrder(head.root);
	putchar('\n');
	InOrder_Norecursion(&head);
	putchar('\n');
	PostOrder(head.root);
	putchar('\n');
	PostOrder_Norecursion(&head);
	putchar('\n');
	PostOrder_Norecursion2(&head);
	putchar('\n');
	Level_traversal(head.root);
	putchar('\n');
	RS_Level_traversal(head.root);
	putchar('\n');
	S_Level_traversal(head.root);
	putchar('\n');
	return 0;
}
*/