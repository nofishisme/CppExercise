#pragma once
#ifndef DYNAMIC_ARR_STACK_H
#define DYNAMIC_ARR_STACK_H
#include <stdbool.h>

#define INITIALSIZE 10

typedef char ElemType;

typedef struct {
	ElemType* elements;   // 指向动态数组
	int size;	// 元素的个数
	int capacity; // 数组的容量
} Stack;

Stack* stack_create();
void stack_destroy(Stack* s);

void stack_push(Stack* s, ElemType val);
void stack_pop(Stack* s);
ElemType  stack_peek(Stack* s);
bool is_empty(Stack* s);

#endif // !DYNAMIC_ARR_STACK_H