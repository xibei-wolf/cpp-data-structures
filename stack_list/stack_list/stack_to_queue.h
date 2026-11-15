#pragma once
#include "stack_list.h"
typedef struct TSTQueue {
	LinkStack S1;
	LinkStack S2;
}TSTQueue;

void Init_Two_Stack_to_Queue(TSTQueue* tstq);
bool push_TSTQ(TSTQueue* tstq, ELEM_TYPE val);
bool pop_TSTQ(TSTQueue* tstq);
ELEM_TYPE Front_TSTQ(TSTQueue* tstq);
