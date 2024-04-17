#pragma once
#ifndef LINKLISTQUEUE_H
#define LINKLISTQUEUE_H

#include <stdbool.h>

// 定义队列中的元素类型
typedef int ElemType;

// 队列节点的结构
typedef struct node_s {
	ElemType data;
	struct node_s* next;
} QueueNode;

// 队列的结构
typedef struct {
	QueueNode* front;  // 队列的头部
	QueueNode* rear;   // 队列的尾部
	int size;
} LinkedListQueue;

// 函数声明
LinkedListQueue* create_queue();
void destroy_queue(LinkedListQueue* q);

bool enqueue(LinkedListQueue* q, ElemType element);
ElemType dequeue(LinkedListQueue* q);
ElemType peek_queue(LinkedListQueue* q);

bool is_empty(LinkedListQueue* q);


#endif // !LINKLISTQUEUE_H
