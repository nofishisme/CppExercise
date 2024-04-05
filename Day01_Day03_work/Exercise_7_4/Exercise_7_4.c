#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
void test0() {
	int a, b;
	printf("输入第一个数字：");
	scanf("%d", &a);
	printf("输入第二个数字：");
	scanf("%d", &b);
	printf("交换两个数字前：\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	printf("交换两个数字后：\n");
	swap(&a, &b);
	printf("a: %d\n", a);
	printf("b: %d\n", b);
}

int main(void)
{
	test0();
	return 0;
}