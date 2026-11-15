#pragma once
#define INITSIZE 10
typedef char ELEM_TYPE;
typedef struct stack {
	ELEM_TYPE* base;
	int top;
	int stacksize;
}sqstack,*psqstack;
void Init(psqstack ps);
bool Push(psqstack ps, ELEM_TYPE val);//(»Î’ª/—π’ª)
bool Pop(psqstack ps);//(≥ˆ’ª/µØ’ª)
ELEM_TYPE Top(psqstack ps);
bool Empty(psqstack ps);
bool Full(psqstack ps);
static void Inc(psqstack ps);
int Size(psqstack ps);
void Clear(psqstack ps);
void Destroy(psqstack ps);
void Print(psqstack ps);
