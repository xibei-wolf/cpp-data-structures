#pragma once
typedef int ELEM_TYPE;
typedef struct List_Node {
	ELEM_TYPE data;
	struct List_Node* next;
}List_Node,*PList_Node;

typedef struct LinkStack {
	int count;
	PList_Node top;
}LinkStack,*PlinkStack;

void Init(PlinkStack ptr);
bool push(PlinkStack ptr, ELEM_TYPE val);
bool pop(PlinkStack ptr);
void destroy(PlinkStack ptr);
bool Empty(PlinkStack ptr);
int Getlenth(PlinkStack ptr);
ELEM_TYPE Top(PlinkStack ptr);
void show(PlinkStack ptr);




