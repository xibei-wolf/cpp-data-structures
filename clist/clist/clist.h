#pragma once
typedef int ELEM_TYPE;

typedef struct clist {
	ELEM_TYPE data;
	struct clist *next;
}CNode,*PNode;

void Init_Clist(PNode head);
bool Insert_head(PNode head,ELEM_TYPE val);
bool Insert_tail(PNode head,ELEM_TYPE val);
bool Insert_loc(PNode head,ELEM_TYPE val,int loc);
bool Del_head(PNode head);
bool Del_tail(PNode head);
bool Del_loc(PNode head,int loc);
bool Del_val(PNode head, ELEM_TYPE val);
bool Del_all(PNode head, ELEM_TYPE val);
PNode Search(PNode head, ELEM_TYPE val);
void Destroy(PNode head);
void Destroy1(PNode head);
bool Is_empty(PNode head);
void Print(PNode head);
int Get_length(PNode head);




