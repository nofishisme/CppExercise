#pragma once
#ifndef LINKLISTQUEUE_H
#define LINKLISTQUEUE_H

#include <stdbool.h>

// ��������е�Ԫ������
typedef int ElemType;

// ���нڵ�Ľṹ
typedef struct node_s {
	ElemType data;
	struct node_s* next;
} QueueNode;

// ���еĽṹ
typedef struct {
	QueueNode* front;  // ���е�ͷ��
	QueueNode* rear;   // ���е�β��
	int size;
} LinkedListQueue;

// ��������
LinkedListQueue* create_queue();
void destroy_queue(LinkedListQueue* q);

bool enqueue(LinkedListQueue* q, ElemType element);
ElemType dequeue(LinkedListQueue* q);
ElemType peek_queue(LinkedListQueue* q);

bool is_empty(LinkedListQueue* q);


#endif // !LINKLISTQUEUE_H
