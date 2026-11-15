#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"



void Init_List(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	head->next = nullptr;
}

bool Insert_H(PNode head, Elem_Type val) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode q;
	q = (Node*)malloc(sizeof(Node));
	if (q == nullptr) {
		exit(EXIT_FAILURE);
	}
	q->data = val;
	q->next = head->next;
	head->next = q;
	return true;
}
bool Insert_T(PNode head, Elem_Type val) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode q,p;
	p = (PNode)malloc(sizeof(Node));
	if (p == nullptr) {
		exit(EXIT_FAILURE);
	}
	p->data = val;
	p->next = NULL;
	q = head;
	while (q->next != NULL) {
		q = q->next;
	}
	q->next = p;
	
	return true;
}
bool Insert_loc(PNode head, Elem_Type val, int loc) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode q,p;
	q=(PNode)malloc(sizeof(Node));
	q->data = val;
	p = head;
	while (loc--) {
		p = p->next;
	}
	q->next = p->next;
	p->next = q;

	return true;
}

bool Del_H(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	if (Is_empty(head)) {
		return false;
	}
	PNode p = head->next;
	head->next= p->next;
	free(p);
	p = NULL;
	return true;
}
bool Del_T(PNode head) {
	assert(head != nullptr);
	if (head == NULL) {
		exit(EXIT_FAILURE);
	}
	if (Is_empty(head)) {
		return false;
	}
	PNode p = head;
	while (p->next->next!= NULL) {
		p = p->next;
	}
	PNode q = p->next;
	free(q);
	q = NULL;
	p->next = NULL;
	return true;
}
bool Del_loc(PNode head, int loc) {
	assert(head != nullptr);
	assert(loc >= 0 && loc < Getlength(head));
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head;
	while (loc--)
	{
		p = p->next;
	}
	PNode q = p->next;
	p->next = p->next->next;
	free(q);

	return true;
}
bool Del_val(PNode head, Elem_Type val) {
	PNode p = head,q;
	while (p->next!=Search(head,val))
	{	
		p = p->next;
	}
	if (p->next->data == val) {
		q = p->next;
		p->next = q->next;
		free(q);
		return true;
	}
	else return false;
}

bool Del_allval(PNode head, Elem_Type val) {
	assert(head!=nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	while (Del_val(head,val)) {}
	return true;
}

PNode Search(PNode head, Elem_Type val) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head->next;
	while (p!=NULL)
	{
		if (p->data == val) {
			return p;
		}
		p = p->next;
	}
	return NULL;
}
bool Is_empty(PNode head) {
	return head->next == NULL;
}

int Getlength(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p=head->next;
	int num = 0;
	while (p!= NULL) { 
		num++; 
		p = p->next;
	}
	return num;
}
void Destroy_head(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p = head->next;
	while (p!=NULL)
	{
		head->next = p->next;
		free(p);
		p = head->next;
	}
}
void Destroy_nohead(PNode head) {
	assert(head != nullptr);
	if (head == nullptr) {
		exit(EXIT_FAILURE);
	}
	PNode p, q;
	p = head->next;
	q =	NULL;
	while (p!=NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	head->next = NULL;
}
void Print(PNode head) {
	assert(head != nullptr);
	PNode p=head->next;
	while (p!=NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	putchar('\n');
}




void reserve(PNode head) {
	assert(head != nullptr);
	if (head == nullptr)
		exit(EXIT_FAILURE);
	assert(head->next != nullptr);
	assert(head->next->next != nullptr);
	if (head->next == NULL || head->next->next == NULL)
		exit(EXIT_FAILURE);


	PNode p = head->next, q = NULL;
	head->next = NULL;
	while (p!=NULL)
	{
		q = p->next;
		p->next = head->next;
		head->next = p;
		p = q;
	}
	
}
void reserve2(PNode head) {
	assert(head != nullptr);
	if (head == nullptr)
		exit(EXIT_FAILURE);
	PNode p = head->next, q, r;
	q = p->next;
	r = NULL;
	p->next = NULL;
	head->next = NULL;
	while (q!=NULL) {
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	head->next = p;
}

bool intersect(PNode head1, PNode head2) {
	PNode q = head1;
	PNode p = head2;
	while (q->next != NULL)
	{
		q = q->next;
	}
	while (p->next!=NULL)
	{
		p = p->next;
	}
	return p == q;
}
PNode Get_Intersect(PNode head1, PNode head2) {
	bool tag = intersect(head1, head2);
	if (!tag)
		return NULL;
	int len1 = Getlength(head1);
	int len2 = Getlength(head2);
	PNode p = len1 > len2 ? head1 : head2;
	PNode q = len1 < len2 ? head1 : head2;
	for (int i = 0;i < abs(len1 - len2);i++) {
		p = p->next;
	}
	while (p!=q)
	{
		p = p->next;
		q = q->next;
	}
	return p;
}
bool Del_Node(PNode ptr) {
	assert(ptr != NULL&&ptr->next!=NULL);
	if (ptr == NULL||ptr->next==NULL)
		return false;
	PNode p = ptr->next;
	ptr->data = p->data;
	ptr->next = p->next;
	free(p);
	p = NULL;
	return true;
}

PNode Have_Circle(PNode ptr) {
	if(Is_empty(ptr) ){
		return NULL;
	}
	PNode fp = ptr->next, lp = ptr->next->next;
	while (fp!=NULL&&fp!=lp&&fp->next!=NULL)
	{
		lp = lp->next;
		fp = fp->next->next;
	}
	if (fp == NULL || fp->next == NULL)
		return NULL;
	PNode p = ptr->next;
	PNode q = fp;
	while (p!=q)
	{
		p = p->next;
		q = q->next;
	}
	return p;
}
bool RV(PNode ptr) {
	PNode p=ptr->next,tmp1=ptr->next,tmp2=NULL;
	Node q;
	Init_List(&q);
	while (p!=NULL)
	{
		Insert_H(&q, p->data);
		p = p->next;
	}
	tmp2 = q.next;
	while (tmp1!=NULL)
	{
		if (tmp1->data != tmp2->data) {
			return false;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return true;
}