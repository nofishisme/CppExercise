#include "LinkListQueue.h"
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

// ��������
LinkedListQueue* create_queue() {
	LinkedListQueue* que = calloc(1, sizeof(LinkedListQueue));
	ERROR_INFO(que, NULL, "create_queue calloc error.\n");
	return que;
}
//����һ������
void destroy_queue(LinkedListQueue* q) {
	while (q->front) {
		QueueNode* cur = q->front;
		q->front = q->front->next;
		free(cur);
	}
	free(q);
}
//���
bool enqueue(LinkedListQueue* q, ElemType element) {
	QueueNode* tmp = calloc(1, sizeof(QueueNode));
	ERROR_INFO(tmp, NULL, "enqueue calloc error.\n");
	tmp->data = element;
	//�������Ϊ��
	if (is_empty(q)) {
		q->front = tmp;
		q->rear = tmp;
		q->size++;
		return true;
	}
	//������в��գ����ڶ�β����Ԫ��
	q->rear->next = tmp;
	q->rear = tmp;
	q->size++;
	return true;
}
//����
ElemType dequeue(LinkedListQueue* q) {
	//�������Ϊ�գ�����������Сֵ
	if (is_empty(q)) {
		return INT_MIN;
	}
	QueueNode* tmp = q->front;
	ElemType data = tmp->data;
	//����ֻ��һ��Ԫ��
	if (q->front == q->rear) {
		q->front = NULL;
		q->rear = NULL;
		q->size--;
		free(tmp);
		return data;
	}
	//�����ж��Ԫ��
	q->front = q->front->next;
	q->size--;
	free(tmp);
	return data;
}
//��ȡ��ͷԪ��
ElemType peek_queue(LinkedListQueue* q) {
	return q->front->data;
}

bool is_empty(LinkedListQueue* q) {
	return !q->front;
}