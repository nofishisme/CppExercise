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

//创建一个栈
MyStack* create_mystack() {
	MyStack* tmp =  calloc(1, sizeof(MyStack));
	ERROR_INFO(tmp, NULL, "create_mystack calloc error.");
	return tmp;
}

//元素入栈
void stack_push(MyStack* mystack, ElemType data) {
	SNode* tmp = malloc(sizeof(SNode));
	ERROR_INFO(tmp, NULL, "stack_push malloc error.");
	tmp->data = data;
	tmp->next = mystack->top;
	mystack->top = tmp;
	mystack->size++;
}
//元素出栈
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

// 获取栈顶元素
ElemType stack_peek(const MyStack* mystack) {
	return !is_empty(mystack) ? mystack->top->data : INT_MIN;
}

// 判空
bool is_empty(const MyStack* mystack) {
	return mystack->size ? false : true;
}

//删除一个栈
void destroyStack(MyStack* mystack) {
	while (!is_empty(mystack)) {
		stack_pop(mystack);
	}
	free(mystack);
}