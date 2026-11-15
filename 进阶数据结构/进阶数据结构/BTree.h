#pragma once

#define M 3//需要一个阶数M

typedef int ELEMTYPE;//有效元素的数据类型定义
typedef struct {} Record;//记录集结构

//B-的有效节点结构体设计
typedef struct BTNode
{
	int key_num;//1.节点内有效元素个数
	struct BTNode* parent;//2.节点的双亲指针
	ELEMTYPE key_arr[M + 1];//3.节点用来存放多个有效元素的数组
	struct BTNode* ptr_arr[M + 1];//4.节点用来存放多个孩子指针的数组
	Record* recptr[M + 1];//5.节点用来存放多个元素对应的 在磁盘中的记录的地址的数组(用指针指向)
}BTNode;

typedef struct Result {
	bool tag;
	BTNode* pNode;
	int index;
}Result;
/*
B-树常被作为数据库中的索引
所以这里的recptr的作为是将B-树中节点的元素和其实际存储的数据记录相关联
通过recptr，我们可以快速的定位到其在磁盘中存储的具体数据记录，从而就可以
实现高效的查找，插入，删除操作
例如在上述的B-树中，我们找学号为23的学生，我们先找23，找到之后，通过23对应的
recptr指针来快速的获取其家庭住址
*/


//B-的辅助节点结构体设计
typedef struct
{
	BTNode* root;
}BTree;

//实现的函数功能
//工具函数
//1.购买新节点
BTNode* BuyNode();
//2.插入调整

//3.删除调整



//普通函数
//1.初始化
void Init_BTree(BTree* pTree);
//2.插入
void Insert_Split_Adjust(BTree* ptree, BTNode* node);
bool Insert_BTree(BTree* pTree,ELEMTYPE key);
//3.删除
bool Delet_BTree(BTree* pTree, ELEMTYPE key);

//4.查找
BTNode* Search_BTree(BTree* pTree, ELEMTYPE key);
Result* Search_end_BTree(BTree* pTree, ELEMTYPE key);
//5.打印(中序遍历，顺序遍历)
void show_BTree(BTNode* root);