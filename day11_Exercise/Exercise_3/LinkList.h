#pragma once
#ifndef __WY_LINKLIST_H__
#define __WY_LINKLIST_H__
#include <stdbool.h>
typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode;

typedef struct LinkList {
	LNode* head;
	LNode* tail;
	int size;
}LinkList;

// 基础操作函数声明
LinkList* create_linked_list();                     // 创建一个空的链表
void destroy_linked_list(LinkList* list);           // 销毁链表

bool add_before_head(LinkList* list, ElemType data);        // 头部插入结点
bool add_behind_tail(LinkList* list, ElemType data);        // 尾部插入结点
bool add_index(LinkList* list, int index, ElemType data); // 按索引插入结点

LNode* search_by_index(LinkList* list, int index);          // 根据索引搜索结点
LNode* search_by_data(LinkList* list, ElemType data);             // 根据数据搜索结点
bool delete_node_by_data(LinkList* list, ElemType data);         // 根据数据删除结点

bool delete_by_idx(LinkList* list, ElemType index);         // 根据索引删除结点
//打印链表
void printLinkLlist(const LinkList* list);


#endif // !__WY_LINKLIST_H__
