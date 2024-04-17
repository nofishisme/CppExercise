#define _CRT_SECURE_NO_WARNINGS
#include "LinkListQueue.h"
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
	LinkedListQueue* que = create_queue();
	for (int i = 0; i < 15; ++i) {
		enqueue(que, i * i + 1);
	}
	for (int i = 0; i < 10; ++i) {
		printf("%d ", dequeue(que));
	}
	printf("\n");
	destroy_queue(que);
}

int main(void)
{
	test0();
	return 0;
}