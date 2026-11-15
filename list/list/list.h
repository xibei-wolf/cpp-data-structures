#pragma once
typedef int Elem_Type;
typedef struct Node {
	Elem_Type data;
	struct Node* next;
}Node,*PNode;

void Init_List(PNode head);

bool Insert_H(PNode head, Elem_Type val);
bool Insert_T(PNode head, Elem_Type val);
bool Insert_loc(PNode head, Elem_Type val, int loc);

bool Del_H(PNode head);
bool Del_T(PNode head);
bool Del_loc(PNode head, int loc);
bool Del_val(PNode head, Elem_Type val);
bool Del_allval(PNode head, Elem_Type val);

PNode Search(PNode head, Elem_Type val);
bool Is_empty(PNode head);
int Getlength(PNode head);
void Destroy_head(PNode head);
void Destroy_nohead(PNode head);
void Print(PNode head);
//problem
void reserve(PNode head);
void reserve2(PNode head);
bool intersect(PNode head1, PNode head2);
bool Del_Node(PNode ptr);
PNode Have_Circle(PNode ptr);
bool RV(PNode ptr);
