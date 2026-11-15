#pragma once
#include <stdio.h>
#include <queue>
using namespace std;
typedef struct TQTS {
	queue<char> Q1;
	queue<char> Q2;
}TQTS;
bool push_TQTS(TQTS* tqts,char val);
bool pop_TQTS(TQTS* tqts);
char Top_TQTS(TQTS* tqts);

