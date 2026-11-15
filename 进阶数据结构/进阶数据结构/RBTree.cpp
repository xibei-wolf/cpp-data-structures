#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stack>
#include"RBTree.h"
RBNode* BuyRBNode() {
	RBNode* p = (RBNode*)malloc(sizeof(RBNode));
	if (p == NULL)
		exit(EXIT_FAILURE);
	memset(p, 0, sizeof(RBNode));
	return p;
}

RBNode* L_Rotate(RBNode* node) {
	RBNode* father = node->parent;
	RBNode* grandfather = father->parent;
	grandfather->rchild = father->lchild;
	father->lchild = grandfather;
	grandfather->parent = father;
	if (grandfather->rchild != NULL) {
		grandfather->rchild->parent = grandfather;
	}
	
	return father;
}

RBNode* R_Rotate(RBNode* node) {
	RBNode* father = node->parent;
	RBNode* grandfather = father->parent;
	grandfather->lchild = father->rchild;
	father->rchild = grandfather;
	grandfather->parent = father;
	if (grandfather->lchild != NULL) {
		grandfather->lchild->parent = grandfather;
	}
	return father;
}

void Insert(RBTree* tree, RBNode* node) {
	assert(tree != NULL);
	if (tree == NULL)exit(EXIT_FAILURE);
	RBNode* father = node->parent;
	if (father == NULL)
	{
		node->color = BLACK;
		return;
	} 
	if (father->color == BLACK)return;
	RBNode* grandfather = father->parent;
	RBNode* uncle = grandfather->lchild == father ? grandfather->rchild : grandfather->lchild;

	if (uncle != NULL && uncle->color == RED) {

		uncle->color = father->color = BLACK;
		grandfather->color = RED;
		Insert(tree, grandfather);
		return;
	}else
	{
		if (grandfather->lchild == father)
		{
			if (father->lchild == node) {//LL
				grandfather->color = RED;
				father->color = BLACK;
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = R_Rotate(node);
				if (great_grandfather == NULL) tree->root = ptr;
				else {
					if (ptr->val < grandfather->val) great_grandfather->lchild = ptr;
					else great_grandfather->rchild = ptr;
				}
				ptr->parent = great_grandfather;
				return;
			}
			else {//LR
				father->rchild = node->lchild;
				node->lchild = father;
				father->parent = node;
				grandfather->lchild = node;
				node->parent = grandfather;

				if (father->rchild) {
					father->rchild->parent = father;
				}

				grandfather->color = RED;
				node->color = BLACK;

				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = R_Rotate(father);

				if (great_grandfather==NULL) {
					tree->root = ptr;
					ptr->parent = NULL;
				}
				else {
					if (ptr->val < great_grandfather->val)
						great_grandfather->lchild = ptr;
					else
						great_grandfather->rchild = ptr;
					ptr->parent = great_grandfather;
				}
				return;
			}
		}
		else{
			if (father->rchild == node) {//RR
				grandfather->color = RED;
				father->color = BLACK;
				
				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = L_Rotate(node);

				if (great_grandfather == NULL) {
					tree->root = ptr;
					ptr->parent = NULL;

				}
				else {
					if (ptr->val < great_grandfather->val)
						great_grandfather->lchild = ptr;
					else
						great_grandfather->rchild = ptr;
					ptr->parent = great_grandfather;
				}
				return;
			}
			else {//RL
				father->lchild = node->rchild;
				node->rchild = father;
				father->parent = node;
				grandfather->rchild = node;
				node->parent = grandfather;

				if (father->lchild) {
					father->lchild->parent = father;
				}

				node->color = BLACK;
				grandfather->color = RED;


				RBNode* great_grandfather = grandfather->parent;
				RBNode* ptr = L_Rotate(father);

				if (great_grandfather==NULL)
					tree->root = ptr;
				else {
					if (ptr->val < great_grandfather->val)
						great_grandfather->lchild = ptr;
					else
						great_grandfather->rchild = ptr;
					ptr->parent = great_grandfather;
				}
				return;
			}
		}
	}
}


void RB_Init(RBTree* tree) {
	assert(tree != NULL);
	if (tree == NULL)exit(EXIT_FAILURE);
	tree->root = NULL;
}

bool RB_Insert(RBTree* tree, ELEMENT val) {
	assert(tree != NULL);
	if (tree == NULL) exit(EXIT_FAILURE);
	RBNode* pnew = BuyRBNode();
	pnew->val = val; 
	RBNode* p = tree->root;
	RBNode* pp = NULL;
	if (p == NULL) {
		tree->root = pnew;
		pnew->color = BLACK;
		return true;
	}
	while (p != NULL && p->val!=val)
	{
		pp = p;
		p = p->val > val ? p->lchild : p->rchild;
	}

	if (p!=NULL&&p->val == val) {
		free(pnew);
		return true;
	}
	p = pnew;
	p->parent = pp;

	if (pp->val > p->val)
		pp->lchild = p;
	else
		pp->rchild = p;

	

	if (pp->color == RED) {
		Insert(tree, p);
	}

	return true;
}

void Delet(RBTree* tree, RBNode* node,bool tag) 
{
	assert(tree != 0);
	if (tree == NULL)exit(EXIT_FAILURE);
	RBNode* parent = node->parent;
	RBNode* bro= NULL;
	RBNode* child = node->lchild !=NULL ? node->lchild : node->rchild;
	printf("%d进入调整函数\n", node->val);

	if (tag && child != NULL) {//单子
		printf("%d单子 %d\n", node->val,child->val);
		if (parent == NULL) {
			tree->root = child;
		}
		else {
			if (child->val < parent->val) parent->lchild = child;
			else parent->rchild = child;
		}
		child->parent = parent;
		child->color = BLACK;
		free(node);
		return;
	}

	if (child == NULL) {//无子
		printf("%d已无子\n", node->val);
		if (tag && parent == NULL) {
			tree->root = NULL;
			free(node);
			printf("%d已删除\n", node->val);
			return;
		}

		if (tag && node->color == RED) {
			if (parent->lchild == node) parent->lchild = NULL;
			else parent->rchild = NULL;
			free(node);
			return;
		}
		else {//自己是黑色
			bro = parent->lchild == node ? parent->rchild : parent->lchild;
			RBNode* grandparent = parent->parent;
			if (bro && bro->color == RED) {//兄弟是红色
				printf("%d兄弟是红", bro->color);
				bro->color = BLACK;
				parent->color = RED;
				RBNode* ptr = node == parent->lchild ? L_Rotate(bro->lchild) : R_Rotate(bro->rchild);
				if (grandparent == NULL) tree->root = ptr;
				else {
					if (ptr->val < grandparent->val) grandparent->lchild = ptr;
					else grandparent->rchild = ptr;
				}
				ptr->parent = grandparent;
				Delet(tree, node, true);
			}
			else {//兄弟是黑色
				printf("%d兄弟是黑", node->val);
				if (tag) {
					if (parent->lchild == node)parent->lchild = NULL;
					else parent->rchild = NULL;
					free(node);
				}
				printf("%d还在", bro->val);
				if (bro->lchild && bro->lchild->color == RED && bro->rchild && bro->rchild->color == RED) {
					printf("%d双红海尔", bro->val);
					if (parent->lchild == bro) {//LL r-s s-p p-黑
						if (grandparent) {
							if (node->val < grandparent->val) grandparent->lchild = R_Rotate(bro->lchild);
							else grandparent->rchild = R_Rotate(bro->lchild);
						}
						else tree->root = R_Rotate(bro->lchild);

						bro->lchild->color = bro->color;
					}
					else {//RR
						if (grandparent) {
							if (node->val < grandparent->val) grandparent->lchild = R_Rotate(bro->rchild);
							else grandparent->rchild = R_Rotate(bro->rchild);
						}
						else tree->root = L_Rotate(bro->rchild);

						bro->rchild->color = bro->color;
					}

					bro->color = parent->color;
					parent->color = BLACK;
					node->parent = grandparent;
					return;
				}
				else if (bro->lchild && bro->lchild->color == RED) {
					printf("%d兄弟左红海尔", node->val);
					if (parent->lchild == bro) {//LL
						if (parent->lchild == bro) {//LL r-s s-p p-黑
							if (grandparent) {
								if (node->val < grandparent->val) grandparent->lchild = R_Rotate(bro->lchild);
								else grandparent->rchild = R_Rotate(bro->lchild);
							}
							else tree->root = R_Rotate(bro->lchild);

							bro->lchild->color = bro->color;
							bro->color = parent->color;
							parent->color = BLACK;
							node->parent = grandparent;
						}
						else {//RL r-p p-黑
							RBNode* r = node->lchild;
							bro->lchild = r->rchild;
							r->rchild = bro;
							bro->parent = r;
							parent->rchild = r;
							if (grandparent) {
								if (node->val < grandparent->val) grandparent->lchild = L_Rotate(bro);
								else grandparent->rchild = L_Rotate(bro);
							}
							else tree->root = L_Rotate(bro);
							r->parent = grandparent;
							r->color = parent->color;
							parent->color = BLACK;
						}
						return;
					}
				}
				else if (bro->rchild && bro->rchild->color == RED) {
					printf("%d兄弟右红海尔", node->val);
					if (parent->rchild == bro) {//RR
						if (grandparent) {
							if (node->val < grandparent->val) grandparent->lchild = L_Rotate(bro->rchild);
							else grandparent->rchild = L_Rotate(bro->rchild);
						}
						else tree->root = L_Rotate(bro->rchild);
						bro->rchild->color = bro->color;
						bro->color = parent->color;
						parent->color = BLACK;
						node->parent = grandparent;
					}
					else {//LR
						RBNode* r = node->rchild;
						bro->rchild = r->lchild;
						r->lchild = bro;
						bro->parent = r;
						parent->lchild = r;
						if (grandparent) {
							if (node->val < grandparent->val) grandparent->lchild = R_Rotate(bro);
							else grandparent->rchild = R_Rotate(bro);
						}
						else tree->root = R_Rotate(bro);
						r->parent = grandparent;
						r->color = parent->color;
						parent->color = BLACK;
					}
						return;
				}
				else {//无红孩儿     兄弟变红 
					printf("%d无红海尔", bro->color);
					bro->color = RED;
					printf("%d变红", bro->color);
					//双黑上移 直接变黑 结束
					if (parent->color == RED || parent->parent == NULL)
					{
						parent->color = BLACK;
						return;
					}
					else {//遇到黑色
						Delet(tree, parent, false);
					}
				}
			}
		}
		
	}

}

bool RB_Delet(RBTree* tree, ELEMENT val) {
	assert(tree != NULL);
	if (tree == NULL)exit(EXIT_FAILURE);
	RBNode* p = tree->root;
	printf("%d待删除\n", val);
	if (p == NULL)return false;
	p = RB_Search(tree, val);
	printf("%d进入删除函数\n", p->val);

	if (p->lchild!=NULL && p->rchild != NULL) {//双子
		RBNode* tmp = p->rchild;
		printf("%d双子\n", p->val);
		while (tmp->lchild!=NULL)
		{
			tmp = tmp->lchild;
		}
		p->val = tmp->val;
		p = tmp;
		Delet(tree,p,true);
		return true;
	}
	else Delet(tree, p, true);

}

RBNode* RB_Search(RBTree* tree, ELEMENT val) {
	assert(tree != NULL);
	if (tree == NULL)exit(EXIT_FAILURE);
	RBNode* p = tree->root;
	while(p!=NULL&&p->val!=val)
		p = p->val > val ? p->lchild : p->rchild;
	return p;
}


void show(RBNode* node) {
	if (node == NULL)
		return;
	show(node->lchild);
	printf("%d ",node->val);
	show(node->rchild);
}
void show(RBTree* Tree) {
	assert(Tree != NULL);
	if (Tree == NULL)exit(EXIT_FAILURE);
	std::stack<RBNode*> st;
	st.push(Tree->root);
	bool tag = true;
	while (!st.empty())
	{
		while (tag && st.top()->lchild != NULL)
			st.push(st.top()->lchild);
		RBNode* p = st.top();
		printf("%d ", p->val);
		st.pop();
		tag = false;
		if (p->rchild != NULL) {
			st.push(p->rchild);
			tag = true;
		}
	}
}


/*
int main() {
	RBTree head;
	RB_Init(&head);
	RB_Insert(&head, 17);
	RB_Insert(&head, 18);
	RB_Insert(&head, 23);
	RB_Insert(&head, 34);
	RB_Insert(&head, 27);
	RB_Insert(&head, 15);
	RB_Insert(&head, 9);
	RB_Insert(&head, 6);
	RB_Insert(&head, 8);
	RB_Insert(&head, 5);
	RB_Insert(&head, 25);


	show(head.root);
	putchar('\n');
	RB_Delet(&head, 18);
	RB_Delet(&head, 9);
	RB_Delet(&head, 34);
	show(head.root);
	return 0; 
}*/