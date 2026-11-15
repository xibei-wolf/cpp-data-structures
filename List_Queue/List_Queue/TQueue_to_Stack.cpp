#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <queue>
#include <assert.h>
#include "TQueue_to_Stack.h"
using namespace std;
bool push_TQTS(TQTS* tqts, char val) {
	assert(tqts != NULL);
	if (tqts == NULL)return false;
	tqts->Q2.push(val);
	return true;
}
bool pop_TQTS(TQTS* tqts) {
	assert(tqts != NULL);
	if (tqts == NULL)return false;
	if (tqts->Q1.empty() && tqts->Q2.empty())return false;
	if (!tqts->Q2.empty()) {
		while (tqts->Q2.size() != 1)
		{
			char tmp = tqts->Q2.front();
			tqts->Q2.pop();
			tqts->Q1.push(tmp);
		}
		tqts->Q2.pop();
		return true;
	}
	
	else {
		while (tqts->Q1.size() != 1)
		{
			char tmp = tqts->Q1.front();
			tqts->Q1.pop();
			tqts->Q2.push(tmp);
		}
		tqts->Q1.pop();
		return true;
	}
}
char Top_TQTS(TQTS* tqts) {
	assert(tqts != NULL);
	if (tqts == NULL)return false;
	if (!tqts->Q2.empty()) {
		while (tqts->Q2.size() != 1)
		{
			char tmp = tqts->Q2.front();
			tqts->Q2.pop();
			tqts->Q1.push(tmp);
		}
		char t= tqts->Q2.front();
		tqts->Q1.push(t);
		return t;
	}

	else {
		while (tqts->Q1.size() != 1)
		{
			char tmp = tqts->Q1.front();
			tqts->Q1.pop();
			tqts->Q2.push(tmp);
		}
		char t=tqts->Q1.front();
		tqts->Q2.push(t);
		return t;
	}
}