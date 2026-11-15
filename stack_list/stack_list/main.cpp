#define _CRT_SECURE_NO_WARNINGS 
#include "stack_list.h"
#include <stdio.h>
#include "stack_to_queue.h"
//int main() {
//	LinkStack ls;
//	Init(&ls);
//	for (int i = 0;i < 10;i++) {
//		push(&ls, i * 10);
//	}
//	printf("%d\n", Top(&ls));
//	pop(&ls);
//	destroy(&ls);
//	show(&ls);
//
//	return 0;
//}

int main() {
	TSTQueue head;
	Init_Two_Stack_to_Queue(&head);
	for (int i = 1;i < 10;i++) {
		push_TSTQ(&head, i*10);
	}
	for (int i = 1;i < 10;i++) {
		pop_TSTQ(&head);
	}
	push_TSTQ(&head,500);
	printf("%d\n", Front_TSTQ(&head));
	return 0;
}

