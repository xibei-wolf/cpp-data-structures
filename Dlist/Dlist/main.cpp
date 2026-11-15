#define _CRT_SECURE_NO_WARNINGS 
#include "dlist.h"
#include <stdio.h>
int main() {
	DNode dlist;
	Init_DNode(&dlist);
	for (int i = 1;i <= 5;i++) {
		Insert_head(&dlist, i * 10);
	}
	for (int i = 1;i<=5;i++) {
		Insert_tail(&dlist, i * 10);
	}
	Insert_pos(&dlist, 900,8);
	//Del_head(&dlist);
	Del_tail(&dlist);
	Del_pos(&dlist, 2);
	Del_all(&dlist, 40);
	Destroy2(&dlist);
	Show(&dlist);
	Show_Tail(&dlist);
	return 0;
}