#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "clist.h"
#include <assert.h>
#include <stdlib.h>
void Init_Clist(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	head->next = head;
}
bool Insert_head(PNode head,ELEM_TYPE val) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = (PNode)malloc(sizeof(CNode));
	if (p == nullptr) {
		exit(1);
	}
	p->data = val;
	p->next = head->next;
	head->next = p;
	return true;
}
bool Insert_tail(PNode head, ELEM_TYPE val) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = (PNode)malloc(sizeof(CNode)),q=head;
	p->data = val;
	while (q->next!=head) {
		q = q->next;
	}
	p->next = q->next;
	q->next = p;
	return true;
}
bool Insert_loc(PNode head, ELEM_TYPE val, int loc) {
	assert(head!=nullptr);
	assert(loc >= 0&&loc<Get_length(head));
	if (head == NULL) {
		exit(EXIT_FAILURE);
	}
	PNode p = (PNode)malloc(sizeof(CNode)),q=head;
	p->data = val;
	while (loc--) {
		q = q->next;
	}
	p->next = q->next;
	q->next = p;
	return true;
}
bool Del_head(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head->next;
	head->next = p->next;
	free(p);
	p = NULL;
	return true;
}
bool Del_tail(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head,q;
	while (p->next->next!= head) {
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	free(q);
	q = NULL;
	return true;
}
bool Del_loc(PNode head, int loc) {
	assert(head != nullptr);
	assert(loc >=0 && loc < Get_length(head));
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head,q;
	while (loc--) {
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	free(q);
	q = NULL;
	return true;
}
bool Del_val(PNode head, ELEM_TYPE val) {
	assert(head != NULL);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head;
	while (p->next!=head)
	{
		if (p->next->data == val) {
			PNode q = p->next;
			p->next = q->next;
			free(q);
			q = NULL;
			return true;
		}
		else p = p->next;
	}
	return false;
}
bool Del_all(PNode head, ELEM_TYPE val) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	while (Search(head,val)) {
		Del_val(head, val);
	}
	return true;
}
PNode Search(PNode head, ELEM_TYPE val) {
	PNode p = head->next;
	while (p!=head) {
		if (p->data == val)
			return p;
		else p = p->next;
	}
	return NULL;
}

void Destroy(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head->next;
	while (p != head) {
		head->next = p->next;
		free(p);
		p = head->next;
	}
}
void Destroy1(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head->next, q=NULL;
	while (p != head) {
		q = p->next;
		free(p);
		p =q;
	}
	p->next = p;
}
bool Is_empty(PNode head) {
	return head->next==head;
}
void Print(PNode head) {
	PNode p = head->next;
	while (p!=head)
	{
		printf("%d ", p->data);
		p = p->next;
	}
}
int Get_length(PNode head) {
	PNode p = head->next;
	int num = 0;
	while (p!=head) {
		num++;
		p = p->next;
	}
	return num;
}
