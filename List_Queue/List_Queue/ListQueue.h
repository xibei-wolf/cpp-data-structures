#pragma once
typedef int ELEM_TYPE;
typedef struct LQ_Node {
	ELEM_TYPE data;
	struct LQ_Node* next;
}LQ_Node,*PLQ_Node;
typedef struct List_Queue {
	PLQ_Node front;
	PLQ_Node rear;
}List_Queue,*PList_Queue;

void Init_LQ(PList_Queue plq);
bool Push(PList_Queue plq,ELEM_TYPE val);
bool Pop(PList_Queue plq);
ELEM_TYPE Front(PList_Queue plq);
PLQ_Node Search(PList_Queue plq, ELEM_TYPE val);
int Get_Size(PList_Queue plq);
bool Empty(PList_Queue plq);
void clear(PList_Queue plq);
void destroy(PList_Queue plq);
void show(PList_Queue plq);
