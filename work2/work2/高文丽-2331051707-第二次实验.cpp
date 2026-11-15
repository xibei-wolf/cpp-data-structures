#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct dlnode {
	char data;
	struct dlnode* prior, * next;
}DLNode;
DLNode* CreateDLNode() {
	DLNode* head, * s;
	char x;
	head = (DLNode*)malloc(sizeof(DLNode));
	head->next = head;
	head->prior = head;
	printf("Input any char string:\n");
	scanf("%c", &x);
	while (x != '\n') {
		s = (DLNode*)malloc(sizeof(DLNode));
		s->data = x;
		s->prior = head;
		s->next = head->next;
		head->next->prior = s;
		head->next = s;
		scanf("%c", &x);
	}
	return head;
}
DLNode* Get_DLinkList(DLNode* head, int i) {
	DLNode* p = head;
	int j = 0;
	while (p->next != head && j < i) {
		j++;
		p = p->next;
	}
	if (p->next != head)
		return p;
	else
		return NULL;
}
void Insert_DLinkList(DLNode* head, int i, char x) {
	DLNode* p, * s;
	p = Get_DLinkList(head, i - 1);
	if (p == NULL)
		printf("Error:\n");
	else
	{
		s = (DLNode*)malloc(sizeof(DLNode));
		s->data = x;
		s->prior = p;
		s->next = p->next;
		p->next->prior = s;
		p->next = s;
	}
}
void Del_DLinkList(DLNode* head, int i) {
	DLNode* p;
	p = Get_DLinkList(head, i);
	if (p == NULL)
		printf("can not find the node\n");
	else {
		p->next->prior = p->prior;
		p->prior->next = p->next;
		free(p);
	}
}
void print1(DLNode* head) {
	DLNode* p = head->next;
	while (p != head) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}
void print2(DLNode* head) {
	DLNode* p = head->prior;
	while (p != head) {
		printf("%c", p->data);
		p = p->prior;
	}
	printf("\n");
}
void main() {
	DLNode* h, * p;
	int i;
	char x;
	h = CreateDLNode();
	printf("Output list for next:\n");
	print1(h);
	printf("Output list for piror:\n");
	print2(h);
	printf("Input order and search to element:\n");
	scanf("%d", &i);
	p = Get_DLinkList(h, i);
	if (p != NULL)
		printf("Element is %c\n", p->data);
	else
		printf("Search fail!\n");
	printf("Insert a element,Input site and value of element:\n");
	scanf("%d %c", &i, &x);
	Insert_DLinkList(h, i, x);
	print1(h);
	printf("Delete a elemnt,Input site of element:\n");
	scanf("%d", &i);
	Del_DLinkList(h, i);
	print1(h);
}