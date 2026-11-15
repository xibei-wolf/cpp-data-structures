#pragma once
#define MaxSize 10
typedef int ELEM_TYPE;
typedef struct CQueue{
	ELEM_TYPE* base;
	int front;
	int rear;
}CQueue,*PCQueue;
void Init_CQueue(PCQueue pcq);
bool push(PCQueue pcq,ELEM_TYPE val);
bool pop(PCQueue pcq);
ELEM_TYPE Front(PCQueue pcq);
int Search(PCQueue pcq, ELEM_TYPE val);
bool Empty(PCQueue pcq);
bool Full(PCQueue pcq);
int Get_size(PCQueue pcq);
void Clear(PCQueue pcq);
void Destroy(PCQueue pcq);
void show(PCQueue pcq);

