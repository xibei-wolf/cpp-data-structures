#pragma once
typedef int ELEM_TYPE;
#define INISIZE 20
typedef struct SeqList
{
	ELEM_TYPE* elem;
	int len;
	int listsize;
}SeqList,*PSeqList;
typedef struct list
{
	ELEM_TYPE data;
	struct list* next;
}List,*PList;

void Init_SeqList(PSeqList psl);
void Insert_SeqList(PSeqList psl, ELEM_TYPE val);
void Del_Seq(PSeqList psl);
bool Empty(PSeqList psl);
bool Full(PSeqList psl);
void Increase(PSeqList psl);
void Insert_9(PSeqList psl, ELEM_TYPE val);//第9题
bool cmp(PSeqList pa,PSeqList pb);//第10题
void reverse(PSeqList psl);//第11题
void show_seq(PSeqList psl);


void Init_List(PList head);
void Inset_List(PList head,ELEM_TYPE val);
void Insert_12(PList a, PList b);
bool find(PList a,ELEM_TYPE val);
void fun_13(PList a, PList b, PList c);
void fun_R13(PList a, PList b, PList c);
void Show_List(PList head);



