#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "clist.h"
int main() {
	CNode head;
	Init_Clist(&head);
	for (int i = 0;i < 10;i++) {
		Insert_head(&head, (i+1) * 10);
	}
	Insert_tail(&head, 500);
	Insert_loc(&head, 500, 5);
	Del_head(&head);
	//Del_tail(&head);
	printf("%d\n", Get_length(&head));
	Print(&head);
	putchar('\n');
	//Del_loc(&head, 5);
	Del_all(&head,500);
	Destroy1(&head);
	printf("%d\n", Get_length(&head));
	Print(&head);

	return 0;
}