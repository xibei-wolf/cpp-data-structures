#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Seqlist.h"
void Init_SeqList(PSeqList psl) {
	assert(psl != nullptr);
	if (psl == nullptr) {
		exit(EXIT_FAILURE);
	}
	psl->elem=(ELEM_TYPE*)malloc(sizeof(ELEM_TYPE)*INIT_SIZE);
	if (psl->elem == NULL) {
		exit(EXIT_FAILURE);
	}
	psl->length = 0;
	psl->listsize = INIT_SIZE;
}
bool Insert_SeqList(PSeqList psl, ELEM_TYPE val) {
	assert(psl != nullptr);
	if (psl == nullptr) {
		exit(EXIT_FAILURE);
	}
	if (Is_Full(psl)) {
		Increase(psl);
	}
	for (int i = psl->length;i>=0;i--) {
		psl->elem[i + 1] = psl->elem[i];
	}
	psl->elem[0] = val;
	psl->length++;
	return true;
}
bool Insert_loc(PSeqList psl, ELEM_TYPE val, int loc) {
	assert(psl != nullptr);
	assert(loc >= 0 && loc <= psl->length);
	if (psl == nullptr) {
		exit(EXIT_FAILURE);
	}
	if (Is_Full(psl)) {
		Increase(psl);
	}
	for (int i = psl->length;i>=loc ;i--) {
		psl->elem[i + 1] = psl->elem[i];
	}
	psl->elem[loc] = val;
	psl->length++;
	return true;

}
bool Del_SeqList(PSeqList psl,int loc) {//∞¥Œª÷√…æ
	assert(psl != nullptr);
	
	if (psl == nullptr) {
		exit(EXIT_FAILURE);
	}
	if (Is_Empty(psl)) {
		return false;
	}
	for (int i = loc;i < psl->length;i++) {
		psl->elem[i] = psl->elem[i + 1];
	}
	psl->length--;
	return true;
}
int del_allval(PSeqList psl, ELEM_TYPE val) {
	int count = 0, index;
	for (int i = 0;i < psl->length;i++) {
		if (psl->elem[i] == val)
			count++;
	}
	for (int j = 0;j < count;j++) {
		index = Search_SeqList(psl, val);
		Del_SeqList(psl, index);
	}
	return true;
}
int Search_SeqList(PSeqList psl, ELEM_TYPE val) {
	assert(psl != nullptr);
	if (psl == nullptr) {
		exit(EXIT_FAILURE);
	}
	for (int i = 0;i < psl->length;i++) {
		if (psl->elem[i] == val)
			return i;
	}
	return -1;

}
bool Is_Empty(PSeqList psl) {
	return psl->length == 0;
}
bool Is_Full(PSeqList psl) {
	return psl->length == psl->listsize;
}
void Increase(PSeqList psl) {
	ELEM_TYPE* tmp = (ELEM_TYPE*)realloc(psl->elem,sizeof(ELEM_TYPE) * 2*psl->listsize);
	if (tmp!= nullptr) {
		psl->elem = tmp;
	}
	psl->listsize *= 2;
}
void Clear(PSeqList psl) {
	psl->length = 0;
}
void Destroy(PSeqList psl) {
	free(psl->elem);
	psl->listsize = psl->length = 0;
}
void Print(PSeqList psl) {
	assert(psl != nullptr);
	if (psl == nullptr) {
		exit(EXIT_FAILURE);
	}
	for (int i = 0;i < psl->length;i++) {
		printf("%d ", psl->elem[i]);
	}
	printf("\n");
}
int main() {
	SeqList p;
	Init_SeqList(&p);
	for (int i = 0;i < 10;i++) {
		Insert_SeqList(&p,i);
	}
	Print(&p);
	Insert_loc(&p, 9,5);
	Print(&p);
	Insert_loc(&p, 9, 7);
	Print(&p);
	del_allval(&p, 9);
	Print(&p);
	Clear(&p);
	Print(&p);
	printf("%d", p.listsize);
	Destroy(&p);
	printf("%d",p.listsize);
	return 0;
}


