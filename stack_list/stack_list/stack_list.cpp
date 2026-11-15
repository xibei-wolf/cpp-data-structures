#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "stack_list.h"

void Init(PlinkStack ptr) {
	assert(ptr != NULL);
	if (ptr == NULL)
		EXIT_FAILURE;
	ptr->count = 0;
	ptr->top = NULL;
}
bool push(PlinkStack ptr, ELEM_TYPE val) {
	assert(ptr != NULL);
	if (ptr == NULL)
		EXIT_FAILURE;
	PList_Node p;
	p = (PList_Node)malloc(sizeof(List_Node));
	if (p == NULL)
		return false;
	p->data = val;
	p->next = NULL;
	p->next = ptr->top;
	ptr->top = p;
	ptr->count++;
	return true;
}
bool pop(PlinkStack ptr) {
	assert(ptr != NULL);
	if (ptr == NULL) return false;
	if (Empty(ptr)) {
		return false;
	}
	PList_Node p = ptr->top;
	ptr->top = p->next;
	free(p);
	p = NULL;
	ptr->count--;
	return true;
}

void destroy(PlinkStack ptr) {
	assert(ptr != NULL);
	if (ptr == NULL)EXIT_FAILURE;
	PList_Node p = ptr->top;
	PList_Node q = NULL;
	while (p!=NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	ptr->count = 0;
	ptr->top = NULL;
}
bool Empty(PlinkStack ptr) {
	assert(ptr != NULL);
	if (ptr == NULL)EXIT_FAILURE;
	return ptr->top == NULL;
}
int Getlenth(PlinkStack ptr) {
	assert(ptr != NULL);
	if(ptr == NULL) EXIT_FAILURE;
	return ptr->count;
}
ELEM_TYPE Top(PlinkStack ptr) {
	if (Empty(ptr))
		exit(1);
	return ptr->top->data;
}
void show(PlinkStack ptr) {
	assert(ptr != NULL);
	if (ptr == NULL) EXIT_FAILURE;
	PList_Node p = ptr->top;
	while (p!=NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}