#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ListQueue.h"
void Init_LQ(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	plq->front = NULL;
	plq->rear = NULL;
}
bool Push(PList_Queue plq, ELEM_TYPE val) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	PLQ_Node p = (PLQ_Node)malloc(sizeof(LQ_Node));
	if (p == NULL)return false;
	p->data = val;
	p->next = NULL;
	if (!Empty(plq)) {
		plq->rear->next = p;
	}
	else {
		plq->front = p;
	}
	plq->rear = p;
	return true;
}
bool Pop(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	if (Empty(plq))return false;
	PLQ_Node p = plq->front;
	plq->front = plq->front->next;
	free(p);
	p = NULL;
	if (plq->front == NULL)plq->rear = NULL;
	return true;
}
ELEM_TYPE Front(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	if (Empty(plq))exit(EXIT_FAILURE);
	return plq->front->data;
}
PLQ_Node Search(PList_Queue plq,ELEM_TYPE val) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	PLQ_Node p = plq->front;
	while (p)
	{
		if (p->data == val)return p;
		if (p == plq->rear)break;
		p = p->next;
	}
	return NULL;
}
int Get_Size(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	PLQ_Node p = plq->front;
	int size = 0;
	while (p)
	{
		size++;
		if (p == plq->rear)return size;
		p = p->next;
	}
	return 0;
}
bool Empty(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	return plq->front==NULL;
}
void clear(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	destroy(plq);
}
void destroy(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	PLQ_Node p=plq->front, q;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	plq->front = plq->rear = NULL;
}
void show(PList_Queue plq) {
	assert(plq != NULL);
	if (plq == NULL)exit(EXIT_FAILURE);
	PLQ_Node p = plq->front;
	while (p)
	{
		printf("%d ", p->data);
		if (p == plq->rear)break;
		p = p->next;
	}
	putchar('\n');
}