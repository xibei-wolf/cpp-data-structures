#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "homework.h"
int main() {
	SeqList va,A,B;
	Init_SeqList(&va);
	Init_SeqList(&A);
	Init_SeqList(&B);
	for (int i = 0;i < 10;i++) {
		Insert_SeqList(&va, i * 10);
	}
	printf("实现第9题前\n");
	show_seq(&va);
	Insert_9(&va, 11);
	printf("实现第9题后\n");
	show_seq(&va);
	putchar('\n');
	for (int i = 0;i < 10;i++) {
		Insert_SeqList(&A, i);
	}
	for (int i = 0;i < 10;i++) {
		Insert_SeqList(&B, i);
	}
	printf("第10题A1 B1\n");
	show_seq(&A);
	show_seq(&B);
	if (cmp(&A, &B)) printf("A1 B1相等\n");
	else printf("A1 B1不相等\n");
	printf("第10题A2 B2\n");
	show_seq(&A);
	B.elem[5] = 50;
	show_seq(&B);
	if (cmp(&A, &B)) printf("A2 B2相等\n");
	else printf("A2 B2不相等\n");
	putchar('\n');
	printf("逆置前\n");
	show_seq(&A);
	reverse(&A);
	printf("逆置后\n");
	show_seq(&A);
	Del_Seq(&A);
	printf("逆置前\n");
	show_seq(&A);
	reverse(&A);
	printf("逆置后\n");
	show_seq(&A);
	putchar('\n');


	List LA,LB;
	Init_List(&LA);
	Init_List(&LB);
	for (int i = 5;i>=0;i--) {
		Inset_List(&LA, 2*i+1);
	}
	for (int i = 5;i>=1;i--) {
		Inset_List(&LB, 2 * i);
	}
	printf("第12题A B\n");
	Show_List(&LA);
	Show_List(&LB);
	Insert_12(&LA, &LB);
	printf("执行第12题函数后的A\n");
	Show_List(&LA);
	printf("\n");
	List La, Lb,Lc,Ld;
	Init_List(&La);
	Init_List(&Lb);
	Init_List(&Lc);
	Init_List(&Ld);
	for (int i = 5;i >= 1;i--) {
		Inset_List(&La, i);
	}
	for (int i = 5;i >= 1;i--) {
		Inset_List(&Lb, i);
	}
	for (int i = 5;i >= 1;i--) {
		Inset_List(&Lc, i);
	}
	for (int i = 5;i >= 1;i--) {
		Inset_List(&Ld, 2*i+1);
	}
	printf("第13题的A B C\n");
	Show_List(&La);
	Show_List(&Lb);
	Show_List(&Lc);
	fun_13(&La, &Lb, &Lc);
	printf("执行第13题函数后的A\n");
	Show_List(&La);
	printf("第13题的A B C\n");
	Show_List(&Lb);
	Show_List(&Lc);
	Show_List(&Ld);
	fun_R13(&Lb, &Lc, &Ld);
	printf("执行第14题函数后的A\n");
	Show_List(&Lb);



}