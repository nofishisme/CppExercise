#define _CRT_SECURE_NO_WARNINGS
#include "QueueByArray.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

// ��ʼ��һ���ն���
MyQueue* queue_create() {
	MyQueue* tmp = calloc(1, sizeof(MyQueue));
	ERROR_INFO(tmp, NULL, "queue_create calloc error.\n");
	return tmp;
}
// ����һ������
void queue_destroy(MyQueue* q) {
	free(q);
}

// ����
bool is_full(MyQueue* q) {
	return (q->rear + 1) % CAPACITY == q->front;
}
// �п�
bool is_empty(MyQueue* q) {
	return q->front == q->rear;
}

// ���
bool enqueue(MyQueue* q, ElemType element) {
	if (is_full(q)) {
		printf("The queue is full!\n");
		return false;
	}
	q->elements[q->rear] = element;
	q->size++;
	q->rear = (++q->rear) % CAPACITY;
}
// ����
ElemType dequeue(MyQueue* q) {
	if (is_empty(q)) {
		printf("The queue is empty!\n");
		return false;
	}
	ElemType tmp = q->elements[q->front];
	q->front = (++q->front) % CAPACITY;
	q->size--;
	return tmp;
}
// ���ʶ���Ԫ��
ElemType peek(MyQueue* q) {
	return q->elements[q->front];
}