#define _CRT_SECURE_NO_WARNINGS 
#include "ListQueue.h"
#include <stdio.h>
#include "TQueue_to_Stack.h"
//int main() {
//	List_Queue p,q;
//	Init_LQ(&p);
//	Init_LQ(&q);
//	for (int i = 0;i < 10;i++) {
//		Push(&p, i);
//	}
//	Pop(&p);
//	show(&p);
//	//destroy(&p);
//	printf("%d\n", Search(&p, 9)->data);
//	Push(&q, 100);
//	show(&q);
//	destroy(&q);
//	//clear(&q);
//	show(&q);
//	return 0;
//}

int main() {
	TQTS head;
	for (int i = 0;i < 10;i++) {
		push_TQTS(&head,char('a'+i));
	}
	printf("%c\n", Top_TQTS(&head));
	pop_TQTS(&head);
	push_TQTS(&head, 'A');
	printf("%c\n", Top_TQTS(&head));

	return 0;
}