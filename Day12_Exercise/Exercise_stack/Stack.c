#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

//����һ��ջ
MyStack* create_mystack() {
	MyStack* tmp =  calloc(1, sizeof(MyStack));
	ERROR_INFO(tmp, NULL, "create_mystack calloc error.");
	return tmp;
}

//Ԫ����ջ
void stack_push(MyStack* mystack, ElemType data) {
	SNode* tmp = malloc(sizeof(SNode));
	ERROR_INFO(tmp, NULL, "stack_push malloc error.");
	tmp->data = data;
	tmp->next = mystack->top;
	mystack->top = tmp;
	mystack->size++;
}
//Ԫ�س�ջ
ElemType stack_pop(MyStack* mystack) {
	if (is_empty(mystack)) {
		return INT_MIN;
	}
	SNode* tmp = mystack->top;
	ElemType result = tmp->data;
	mystack->top = tmp->next;
	mystack->size--;
	free(tmp);
	return result;
}

// ��ȡջ��Ԫ��
ElemType stack_peek(const MyStack* mystack) {
	return !is_empty(mystack) ? mystack->top->data : INT_MIN;
}

// �п�
bool is_empty(const MyStack* mystack) {
	return mystack->size ? false : true;
}

//ɾ��һ��ջ
void destroyStack(MyStack* mystack) {
	while (!is_empty(mystack)) {
		stack_pop(mystack);
	}
	free(mystack);
}