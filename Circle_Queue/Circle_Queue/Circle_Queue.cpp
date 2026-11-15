#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include "Circle_Queue.h"
void Init_CQueue(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	pcq->base = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * MaxSize);
	if (pcq == NULL)exit(EXIT_FAILURE);
	pcq->front = 0;
	pcq->rear = 0;
}
bool push(PCQueue pcq,ELEM_TYPE val) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	if (Full(pcq))return false;
	pcq->base[pcq->rear] = val;
	pcq->rear=(pcq->rear+1)%MaxSize;
	return true;
}
bool pop(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	if (Empty(pcq)) return false;
	pcq->rear = (pcq->front + 1) % MaxSize;
	return true;
}
ELEM_TYPE Front(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	if (Empty(pcq)) return false;
	return pcq->base[pcq->front];
}
int Search(PCQueue pcq, ELEM_TYPE val) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	for (int i = pcq->front;i != pcq->rear;i = (i + 1) % MaxSize) {
		if (pcq->base[i] == val)
			return i;
	}
	return -1;
}
bool Empty(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	return pcq->front == pcq->rear;
}
bool Full(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	return (pcq->rear + 1) % MaxSize == pcq->front;
}
int Get_size(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	return  (pcq->rear - pcq->front + MaxSize) % MaxSize;
}
void Clear(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	pcq->front=pcq->rear = 0;
}
void Destroy(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	free(pcq->base);
}
void show(PCQueue pcq) {
	assert(pcq != NULL);
	if (pcq == NULL)exit(EXIT_FAILURE);
	for (int i = pcq->front;i != pcq->rear;i = (i + 1) % MaxSize) {
		printf("%d ", pcq->base[i]);
	}
	putchar('\n');
}