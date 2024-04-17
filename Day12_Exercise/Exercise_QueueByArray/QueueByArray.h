#pragma once
#ifndef QUEUEBYARRAY_H
#define QUEUEBYARRAY_H
#include <stdbool.h>

#define CAPACITY 11
typedef int ElemType;

typedef struct {
	ElemType elements[CAPACITY];
	int front;
	int rear;
	int size;
}MyQueue;

// 初始化一个空队列
MyQueue* queue_create();
// 销毁一个队列
void queue_destroy(MyQueue* q);

// 判满
bool is_full(MyQueue* q);
// 判空
bool is_empty(MyQueue* q);

// 入队
bool enqueue(MyQueue* q, ElemType element);
// 出队
ElemType dequeue(MyQueue* q);
// 访问队首元素
ElemType peek(MyQueue* q);


#endif // !QUEUEBYARRAY_H
