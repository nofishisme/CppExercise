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

// ��ʼ��һ���ն���
MyQueue* queue_create();
// ����һ������
void queue_destroy(MyQueue* q);

// ����
bool is_full(MyQueue* q);
// �п�
bool is_empty(MyQueue* q);

// ���
bool enqueue(MyQueue* q, ElemType element);
// ����
ElemType dequeue(MyQueue* q);
// ���ʶ���Ԫ��
ElemType peek(MyQueue* q);


#endif // !QUEUEBYARRAY_H
