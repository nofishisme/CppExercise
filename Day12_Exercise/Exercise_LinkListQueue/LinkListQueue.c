#include "LinkListQueue.h"
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

// 函数声明
LinkedListQueue* create_queue() {
	LinkedListQueue* que = calloc(1, sizeof(LinkedListQueue));
	ERROR_INFO(que, NULL, "create_queue calloc error.\n");
	return que;
}
//销毁一个队列
void destroy_queue(LinkedListQueue* q) {
	while (q->front) {
		QueueNode* cur = q->front;
		q->front = q->front->next;
		free(cur);
	}
	free(q);
}
//入队
bool enqueue(LinkedListQueue* q, ElemType element) {
	QueueNode* tmp = calloc(1, sizeof(QueueNode));
	ERROR_INFO(tmp, NULL, "enqueue calloc error.\n");
	tmp->data = element;
	//如果队列为空
	if (is_empty(q)) {
		q->front = tmp;
		q->rear = tmp;
		q->size++;
		return true;
	}
	//如果队列不空，就在队尾插入元素
	q->rear->next = tmp;
	q->rear = tmp;
	q->size++;
	return true;
}
//出队
ElemType dequeue(LinkedListQueue* q) {
	//如果队列为空，返回整数最小值
	if (is_empty(q)) {
		return INT_MIN;
	}
	QueueNode* tmp = q->front;
	ElemType data = tmp->data;
	//队列只有一个元素
	if (q->front == q->rear) {
		q->front = NULL;
		q->rear = NULL;
		q->size--;
		free(tmp);
		return data;
	}
	//队列有多个元素
	q->front = q->front->next;
	q->size--;
	free(tmp);
	return data;
}
//获取队头元素
ElemType peek_queue(LinkedListQueue* q) {
	return q->front->data;
}

bool is_empty(LinkedListQueue* q) {
	return !q->front;
}