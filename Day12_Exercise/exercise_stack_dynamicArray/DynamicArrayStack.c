#define _CRT_SECURE_NO_WARNINGS
#include "DynamicArrayStack.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

static const int threshold = 1000;

static resize(Stack* s);

//初始化一个栈
Stack* stack_create() {
	Stack* stack = calloc(1, sizeof(Stack));
	ERROR_INFO(stack, NULL, "stack_create calloc error.\n");
	stack->elements = malloc(INITIALSIZE * sizeof(ElemType));
	if (!stack->elements) {
		printf("stack_create elements malloc error.\n");
		free(stack);
		exit(1);
	}
	stack->capacity = INITIALSIZE;
	return stack;
}
void stack_destroy(Stack* s) {
	free(s->elements);
	free(s);
}

void stack_push(Stack* s, ElemType val) {
	if (s->size == s->capacity) {
		resize(s);
	}
	s->elements[s->size++] = val;
}
void stack_pop(Stack* s) {
	if (is_empty(s)) {
		printf("the stack is empty.\n");
		return;
	}
	s->size--;
}
ElemType  stack_peek(Stack* s) {
	if (is_empty(s)) {
		printf("the stack is empty.\n");
		return;
	}
	return s->elements[s->size - 1];
}
bool is_empty(Stack* s) {
	return !s->size;
}

static resize(Stack* s) {
	int old_capacity = s->capacity;
	int new_capacity = old_capacity < threshold ? old_capacity << 1 : old_capacity + (old_capacity >> 1);
	ElemType* tmp = realloc(s->elements, new_capacity * sizeof(ElemType));
	if (!tmp) {
		fprintf(stderr, "stack realloc error.\n");
		return;
	}
	s->elements = tmp;
	s->capacity = new_capacity;
}