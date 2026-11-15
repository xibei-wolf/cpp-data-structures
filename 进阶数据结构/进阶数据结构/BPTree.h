#pragma once

typedef int ELEMTYPE;

#define M 5

typedef enum {LEAF,BRANCH}NodeType;

typedef struct {

}Record;

typedef struct BPNode {
	int key_num;
	ELEMTYPE key_arr[M + 1];
	struct BPNode* ptr_arr[M + 1];
	struct Record* recptr[M + 1];
	struct BPNode* parent;
	NodeType typde;
	struct BPNode* next;
	struct BPNode* front;
}BPNode;

typedef struct BPTree{
	BPNode* root;
	BPNode* head;
}BPTree;

typedef struct Result{
	bool tag;
	BPNode* pNode;
	int index;
}Result;

