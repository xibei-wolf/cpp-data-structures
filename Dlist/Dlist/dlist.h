#pragma once
typedef int ELEM_TYPE;
typedef struct DNode {
	ELEM_TYPE data;
	struct DNode* next;
	struct DNode* prior;
}*PDNode,DNode;

void Init_DNode(PDNode Dlist);
bool Insert_head(PDNode Dlist,ELEM_TYPE val);
bool Insert_tail(PDNode Dlist,ELEM_TYPE val);
bool Insert_pos(PDNode Dlist,ELEM_TYPE val,int pos);
bool Del_head(PDNode Dlist);
bool Del_tail(PDNode Dlist);
bool Del_pos(PDNode Dlist, int pos);
bool Del_val(PDNode Dlist, ELEM_TYPE val);
bool Del_all(PDNode Dlist, ELEM_TYPE val);
bool Is_empty(PDNode Dlist);
void Show(PDNode Dlist);
void Show_Tail(PDNode Dlist);
int Get_length(PDNode Dlist);
bool Destroy1(PDNode Dlist);
bool Destroy2(PDNode Dlist);
PDNode Search(PDNode Dlist,ELEM_TYPE val);