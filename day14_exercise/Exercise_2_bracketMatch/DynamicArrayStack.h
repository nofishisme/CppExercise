#pragma once
#ifndef DYNAMIC_ARR_STACK_H
#define DYNAMIC_ARR_STACK_H
#include <stdbool.h>

#define INITIALSIZE 10

typedef char ElemType;

typedef struct {
	ElemType* elements;   // ָ��̬����
	int size;	// Ԫ�صĸ���
	int capacity; // ���������
} Stack;

Stack* stack_create();
void stack_destroy(Stack* s);

void stack_push(Stack* s, ElemType val);
void stack_pop(Stack* s);
ElemType  stack_peek(Stack* s);
bool is_empty(Stack* s);

#endif // !DYNAMIC_ARR_STACK_H