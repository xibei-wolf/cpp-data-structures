#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dlist.h"
void Init_DNode(PDNode Dlist) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	Dlist->next = NULL;
	Dlist->prior = NULL;
}
bool Insert_head(PDNode Dlist, ELEM_TYPE val) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	PDNode p = (PDNode)malloc(sizeof(DNode));
	p->data = val;
	if (Dlist->next == NULL) {
		p->next = Dlist->next;
		Dlist->next = p;
		p->prior = Dlist;
	}
	else {
		p->next = Dlist->next;
		Dlist->next->prior = p;
		Dlist->next = p;
		p->prior = Dlist;
	}
	return true;
}
bool Insert_tail(PDNode Dlist, ELEM_TYPE val) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	PDNode p = (PDNode)malloc(sizeof(DNode)),q=Dlist;
	p->data = val;
	while (q->next!=NULL)
	{
		q = q->next;
	}
	p->next = q->next;
	p->prior = q;
	q->next = p;
	return true;
}
bool Insert_pos(PDNode Dlist, ELEM_TYPE val, int pos)
{
	assert(Dlist != nullptr);
	assert(pos >= 0 && pos < Get_length(Dlist));
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	if (pos < 0 || pos >= Get_length(Dlist))
		return false;
	PDNode p = (PDNode)malloc(sizeof(DNode)),q=Dlist;
	p->data = val;
	if (pos == 0) Insert_head(Dlist,val);
	else if (pos == Get_length(Dlist)) Insert_tail(Dlist,val);
	else {
		while (pos--)
		{
			q = q->next;
		}
		p->next = q->next;
		q->next->prior = p;
		q->next = p;
		p->prior = q;
	}
	return true;
}
bool Del_head(PDNode Dlist) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	if (Is_empty(Dlist))
		return false;
	PDNode p = Dlist->next;
	if (p->next!= NULL) {
		Dlist->next = p->next;
		p->next->prior = Dlist;
		free(p);
		p = NULL;
	}
	else {
		Dlist->next = p->next;
		free(p);
		p = NULL;
	}
	
	return true;
}
bool Del_tail(PDNode Dlist) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	if (Is_empty(Dlist))
		return false;
	PDNode p = Dlist,q=NULL;
	while (p->next ->next!= NULL) {
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	free(q);
	q = NULL;
	return true;
}
bool Del_pos(PDNode Dlist, int pos) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	assert(pos >= 0 && pos < Get_length(Dlist));
	if (pos < 0 || pos >= Get_length(Dlist))
		return false;
	PDNode p = Dlist, q;
	while (pos--) {
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	q->next->prior = p;
	free(q);
	q = NULL;
	return true;
}
bool Del_val(PDNode Dlist, ELEM_TYPE val) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	if (Is_empty(Dlist))
		return false;
	PDNode p = Dlist, q=NULL;
	while (p->next != NULL&&p->next->data!=val)
	{
		p = p->next;
	}
	if (p->next == NULL)
		return false;
	else if (p->next->next==NULL) {
		q = p->next;
		p->next = q->next;
		free(q);
		q = NULL;

	}else
	{
		q = p->next;
		p->next = q->next;
		q->next->prior = p;
		free(q);
		q = NULL;
	}
	return true;
}
bool Del_all(PDNode Dlist, ELEM_TYPE val) {
	while (Search(Dlist,val))
	{
		Del_val(Dlist, val);
	}
	return true;
}
bool Is_empty(PDNode Dlist) {
	return Dlist->next==NULL;
}
void Show(PDNode Dlist) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	PDNode p = Dlist->next;
	while (p!= NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	putchar('\n');
}
void Show_Tail(PDNode Dlist) {
	assert(Dlist != nullptr);
	if (Dlist == nullptr)
		exit(EXIT_FAILURE);
	PDNode p = Dlist;
	while (p->next!= NULL) {
		p = p->next;
	}
	while (p!= NULL&&p!=Dlist) {
		printf("%d ", p->data);
		p = p->prior;
	}
	putchar('\n');
}
int Get_length(PDNode Dlist) {
	PDNode p = Dlist->next;
	int num = 0;
	while (p!=NULL)
	{
		num++;
		p = p->next;
	}
	return num;
}
bool Destroy1(PDNode Dlist) {
	while (!Is_empty(Dlist))
	{
		Del_head(Dlist);
	}
	return true;
}
bool Destroy2(PDNode Dlist) {
	PDNode p = Dlist->next,q;
	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	Dlist->next = NULL;
	return true;
}

PDNode Search(PDNode Dlist, ELEM_TYPE val) {
	PDNode p = Dlist->next;
	while (p!=NULL&&p->data!=val)
	{
		p = p->next;
	}
	return p;
}