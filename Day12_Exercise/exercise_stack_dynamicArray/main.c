#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "DynamicArrayStack.h"

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

void test0() {
	Stack* mystack = stack_create();
	for (int i = 0; i < 15; ++i) {
		stack_push(mystack, i * i + 1);
	}

	for (int i = 0; i < 15; ++i) {
		printf("%d ", stack_peek(mystack));
		stack_pop(mystack);
	}
	printf("\n");
	stack_destroy(mystack);
}

int main(void)
{
	test0();
	return 0;
}