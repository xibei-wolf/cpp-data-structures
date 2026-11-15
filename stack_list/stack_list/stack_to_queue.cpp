#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <assert.h>
#include "stack_to_queue.h"
#include "stack_list.h"
void Init_Two_Stack_to_Queue(TSTQueue* tstq) {
	Init(&tstq->S1);
	Init(&tstq->S2);
}
bool push_TSTQ(TSTQueue* tstq, ELEM_TYPE val) {
	assert(tstq!=NULL);
	if (tstq == NULL)return false;
	return push(&tstq->S1,val);
}
bool pop_TSTQ(TSTQueue* tstq) {
	assert(tstq != NULL);
	if (tstq == NULL)return false;
	if (Empty(&tstq->S2)) {
		while (!Empty(&tstq->S1))
		{
			ELEM_TYPE tmp = Top(&tstq->S1);
			pop(&tstq->S1);
			push(&tstq->S2, tmp);
		}
	}
	return pop(&tstq->S2);
}
ELEM_TYPE Front_TSTQ(TSTQueue* tstq) {
	assert(tstq != NULL);
	if (tstq == NULL)return false;
	if (Empty(&tstq->S2)) {
		while (!Empty(&tstq->S1))
		{
			ELEM_TYPE tmp = Top(&tstq->S1);
			pop(&tstq->S1);
			push(&tstq->S2,tmp);
		}
	}
	return Top(&tstq->S2);
}