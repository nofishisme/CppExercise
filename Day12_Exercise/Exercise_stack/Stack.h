#pragma once
#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
typedef int ElemType;

typedef struct SNode {
	ElemType data;
	struct SNode* next;
}SNode;

typedef struct MyStack {
	SNode* top;
	int size;
}MyStack;

//����һ��ջ
MyStack* create_mystack();

//Ԫ����ջ
void stack_push(MyStack* mystack, ElemType data);
//Ԫ�س�ջ
ElemType stack_pop(MyStack* mystack);

// ��ȡջ��Ԫ��
ElemType stack_peek(const MyStack* mystack);

// �п�
bool is_empty(const MyStack* mystack);

//ɾ��һ��ջ
void destroyStack(MyStack* mystack);

#endif // !__STACK_H__
