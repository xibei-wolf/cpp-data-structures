#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "stack.h"
void Init(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	ps->base = (ELEM_TYPE*)malloc(sizeof(ELEM_TYPE) * INITSIZE);
	if (ps->base == NULL)
		exit(1);
	ps->top = 0;
	ps->stacksize = INITSIZE;
}
bool Push(psqstack ps, ELEM_TYPE val) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	if (Full)
		Inc(ps);
	ps->base[ps->top++] = val;
	return true;
}
bool Pop(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	if (Empty(ps))
		return false;
	ps->top--;
	return true;
}
ELEM_TYPE Top(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	assert(!Empty(ps));
	if (Empty(ps)) return false;
	else return ps->base[ps->top - 1];
}
bool Empty(psqstack ps) {
	return ps->top == 0;
}
bool Full(psqstack ps) {
	return ps->top == ps->stacksize;
}
static void Inc(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	 ELEM_TYPE* tmp= (ELEM_TYPE*)realloc(ps->base,sizeof(ELEM_TYPE)*(ps->stacksize)*2);
	 if(tmp!=NULL)
	 ps->base = tmp;
	 ps->stacksize = ps->stacksize * 2;
}
int Size(psqstack ps) {
	return ps->top;
}
void Clear(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	ps->top = 0;
}
void Destroy(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	free(ps->base);
	ps->base = NULL;
	ps->stacksize=ps->top = 0;
}
void Print(psqstack ps) {
	assert(ps != NULL);
	if (ps == NULL)
		exit(EXIT_FAILURE);
	int i = 0;
	while (i<ps->top)
	{
		printf("%c ", ps->base[i]);
		i++;
	}
	putchar('\n');
}