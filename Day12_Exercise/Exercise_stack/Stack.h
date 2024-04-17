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

//创建一个栈
MyStack* create_mystack();

//元素入栈
void stack_push(MyStack* mystack, ElemType data);
//元素出栈
ElemType stack_pop(MyStack* mystack);

// 获取栈顶元素
ElemType stack_peek(const MyStack* mystack);

// 判空
bool is_empty(const MyStack* mystack);

//删除一个栈
void destroyStack(MyStack* mystack);

#endif // !__STACK_H__
