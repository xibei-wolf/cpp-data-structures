#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAXSIZE 20
typedef struct {
	int data[MAXSIZE];
	int len;
}SeqList;
SeqList* Init_SeqList() {
	SeqList* L;
	L = (SeqList*)malloc(sizeof(SeqList));
	L->len = 0;
	return L;
}
void CreatList(SeqList* L) {
	printf("Input length of List:\n");
	scanf("%d", &L->len);
	printf("Input int elements of List:\n");
	for (int i = 0;i < L->len;i++) {
		scanf("%d", &L->data[i]);
	}
}
void Insert_SeqList(SeqList* L, int i, int x) {
	if (L->len == 0)
		printf("The List is empty\n");
	else if (i<1 || i>L->len + 1)
		printf("The position is invalid\n");
	else {
		for (int j = L->len - 1; j >= i - 1;j--)
			L->data[j + 1] = L->data[j];
		L->data[i - 1] = x;
		L->len++;
	}
}
void Delete_SeqList(SeqList* L, int i) {
	if (L->len == MAXSIZE - 1)
		printf("The List is full\n");
	else if (i<1 || i>L->len + 1)
		printf("The position is invalid\n");
	else {
		for (int j = i - 1;j < L->len;j++)
			L->data[j] = L->data[j + 1];
		L->len--;
	}
}
int Location_SeqList(SeqList* L, int x) {
	int i = 1;
	while (i < L->len && L->data[i] != x)
		i++;
	if (L->data[i] = x)
		return i;
	else
		return 0;
}
void print(SeqList* L) {
	for (int i = 0;i < L->len;i++)
		printf("%4d", L->data[i]);
	printf("\n");
}
void main() {
	SeqList* s;
	int i, x;
	s = Init_SeqList();
	printf("Creat List:\n");
	CreatList(s);
	printf("Output list:\n");
	print(s);
	printf("Input element and site of insert:\n");
	scanf("%d%d", &i, &x);
	Insert_SeqList(s, i, x);
	printf("Outoput the list:\n");
	print(s);
	printf("Input element site of delete:\n");
	scanf("%d", &i);
	Delete_SeqList(s, i);
	printf("Output the list:\n");
	print(s);
	printf("Input element value of location:\n");
	scanf("%d", &x);
	i = Location_SeqList(s, x) + 1;
	if (i != 0)
		printf("element %d site is %d\n", x, i);
	else
		printf("Not find %d", x);
}