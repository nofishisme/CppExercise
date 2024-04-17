#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

void test0() {
	MyStack* mystack = create_mystack();
	for (int i = 0; i < 5; ++i) {
		stack_push(mystack, i * i + 1);
	}

	for (int i = 0; i < 5; ++i) {
		printf("%d ", stack_pop(mystack));
	}
	printf("\n");
	destroyStack(mystack);
}

int main(void)
{
	test0();
	return 0;
}