#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "homework.h"
void Init_SeqList(PSeqList psl) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	psl->elem = (ELEM_TYPE*)malloc(INISIZE*sizeof(ELEM_TYPE));
	if (psl->elem == NULL)exit(EXIT_FAILURE);
	psl->len = 0;
	psl->listsize = INISIZE;
}
bool Empty(PSeqList psl) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	return psl->len == 0;
}
bool Full(PSeqList psl) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	return psl->len == psl->listsize;
}
void Increase(PSeqList psl) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	ELEM_TYPE* tmp = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * psl->listsize* 2);
	if (tmp != NULL) psl->elem = tmp;
	psl->listsize *= 2;
}
void Insert_SeqList(PSeqList psl, ELEM_TYPE val) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	if (Full(psl)) {
		Increase(psl);
	}
	psl->elem[psl->len] = val;
	psl->len++;
}
void show_seq(PSeqList psl) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	for (int i = 0;i < psl->len;i++) {
		printf("%d ", psl->elem[i]);
	}
	putchar('\n');
}
void Insert_9(PSeqList psl, ELEM_TYPE val) {//第9题 保证插入后有序
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	if (Full(psl)) {
		Increase(psl);
	}
	int i = psl->len-1;
	while (psl->elem[i]>val&&i>=0)
	{
		psl->elem[i + 1] = psl->elem[i];
		i--;
	}
	psl->elem[i] = val;
	psl->len++;
}
void Del_Seq(PSeqList psl) {
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	if (Empty(psl)) exit(EXIT_FAILURE);
	psl->len--;
}
bool cmp(PSeqList pa,PSeqList pb) {//第10题 比较A B
	assert(pa != NULL && pb != NULL);
	if (pa == NULL || pb == NULL) return false;
	int i = 0, j = 0;
	while (i!=pa->len&&j!=pb->len)
	{
		if (pa->elem[i] != pb->elem[j]) {
			return false;
		}
		i++;
		j++;
	}
	return true;
}
void reverse(PSeqList psl){//第11题
	assert(psl != NULL);
	if (psl == NULL)exit(EXIT_FAILURE);
	int mid = psl->len / 2;
	for (int i = 0;i < mid;i++) {
		int tmp = psl->elem[i];
		psl->elem[i] = psl->elem[psl->len - i-1];
		psl->elem[psl->len - i - 1] = tmp;
	}
}

void Init_List(PList head) {
	assert(head != NULL);
	if (head == NULL)exit(EXIT_FAILURE);
	head->next = NULL;
}
void Inset_List(PList head,ELEM_TYPE val) {
	assert(head != NULL);
	if (head == NULL)exit(EXIT_FAILURE);
	PList p = (PList)malloc(sizeof(List));
	if (p == NULL)exit(EXIT_FAILURE);
	p->data = val;
	p->next = head->next;
	head->next = p;
}
void Insert_12(PList a, PList b) {
	assert(a != NULL && b != NULL);
	if (a == NULL || b == NULL) exit(EXIT_FAILURE);
	PList pa = a, pb = b->next,tmp=NULL;
	while (pa->next!=NULL&&pb->next!=NULL)
	{
		if (pa->next->data <= pb->data) {
			pa = pa->next;
		}
		else {
			tmp = pb;
			pb = tmp->next;
			tmp->next = pa->next;
			pa->next = tmp;
		}

	}

}
bool find(PList a,ELEM_TYPE val) {
	assert(a != NULL);
	if (a == NULL)return false;
	if (a->next == NULL)return false;
	PList p = a->next;
	while (p)
	{
		if (p->data == val)return true;
		p = p->next;
	}
	return false;
}
void fun_13(PList a, PList b, PList c) {
	assert(a != NULL && b != NULL&&c!=NULL);
	if (a == NULL || b == NULL||c== NULL) exit(EXIT_FAILURE);
	PList tmp=a;
	while (tmp->next)
	{
		if (find(b, tmp->next->data) && find(c, tmp->next->data)) {
			
			tmp->next = tmp->next->next;
		}
		else {
			tmp = tmp->next;
		}
	}

}
void fun_R13(PList a, PList b, PList c) {
	PList pa = a;
	PList pb = b;
	PList pc = c;
	while (pa->next&&pb->next&&pc->next)
	{
		while (pa->next&&pb->next)
		{
			if (pa->next->data < pb->next->data)
				pa= pa->next;
			else if (pa->data > pb->data)
				pb= pb->next;
			else break;
		}
		while (pa->next && pc->next)
		{
			if (pa->next->data < pc->next->data)
				pa = pa->next;
			else if (pa->next->data > pc->next->data)
				pc= pc->next;
			else break;
		}
		if ((pa->next->data == pb->next->data) &&( pa->next->data == pc->next->data)) {
			pa->next = pa->next->next;
		}
		
	}
}

void Show_List(PList head) {
	assert(head != NULL);
	if (head == NULL)exit(EXIT_FAILURE);
	PList p = head->next;
	while (p!=NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}