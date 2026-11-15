#include <stdio.h>
#include <stdlib.h>
#include "list.h"
int main() {
	Node head;
	Init_List(&head);
	//Init_List(&p);
	for (int i = 0;i < 10;i++) {
		Insert_H(&head, i);
	}
	for (int i = 9;i>=0;i--) {
		Insert_H(&head, i);
	}
	//Insert_T(&head, 100);
	//Insert_loc(&head, 500, 0);
	//Del_H(&head);
	//Del_T(&head);
	//Del_loc(&head, 2);
	//Del_val(&head, 9);
	//Insert_H(&head, 100);
	//Del_allval(&head, 100);
	//Destroy_nohead(&head);
	reserve(&head);
	//reserve2(&head);
	Print(&head);
	printf("%d\n", Getlength(&head));
	if (RV(&head))
	{
		printf("yes");
	}
	else {
		printf("no");
	}
	return 0;
}