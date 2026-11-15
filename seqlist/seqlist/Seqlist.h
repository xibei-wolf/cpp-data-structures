#pragma once
//#ifdef DEBUG
//#define DEBUG
#define INIT_SIZE 10
typedef int ELEM_TYPE;
typedef struct SeqList {
	ELEM_TYPE* elem;
	int length;
	int listsize;
}SeqList,*PSeqList;

void Init_SeqList(PSeqList psl);
bool Insert_SeqList(PSeqList psl,ELEM_TYPE val);
bool Insert_loc(PSeqList psl, ELEM_TYPE val, int loc);
bool Del_SeqList(PSeqList psl, int loc);
int del_allval(PSeqList psl, ELEM_TYPE val);
int Search_SeqList(PSeqList psl,ELEM_TYPE val);
bool Is_Empty(PSeqList psl);
bool Is_Full(PSeqList psl);
void Increase(PSeqList psl);
void Clear(PSeqList psl);
void Destroy(PSeqList psl);
void Print(PSeqList psl);

//#endif // DEBUG

