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

// ����������������
LinkList* create_linked_list();                     // ����һ���յ�����
void destroy_linked_list(LinkList* list);           // ��������

bool add_before_head(LinkList* list, ElemType data);        // ͷ��������
bool add_behind_tail(LinkList* list, ElemType data);        // β��������
bool add_index(LinkList* list, int index, ElemType data); // ������������

LNode* search_by_index(LinkList* list, int index);          // ���������������
LNode* search_by_data(LinkList* list, ElemType data);             // ���������������
bool delete_node_by_data(LinkList* list, ElemType data);         // ��������ɾ�����

bool delete_by_idx(LinkList* list, ElemType index);         // ��������ɾ�����
//��ӡ����
void printLinkLlist(const LinkList* list);


#endif // !__WY_LINKLIST_H__
