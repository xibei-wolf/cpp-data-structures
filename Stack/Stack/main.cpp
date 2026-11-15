#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "stack.h"
int main() {
	sqstack sp;
	Init(&sp);
	for (int i = 0;i < 10;i++) {
		Push(&sp, char('A' + i));
	}
	Pop(&sp);
	printf("%c\n", Top(&sp));
	Print(&sp);
}