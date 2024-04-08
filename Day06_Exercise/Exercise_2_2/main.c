#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void decimalToBinary(int n) {
	if (n <= 1) {
		printf("%d", n);
		return;
	}
	decimalToBinary(n / 2);
	printf("%d", n % 2);
}

void test0() {
	int num;
	printf("请输入一个非负整数：");
	scanf("%d", &num);
	decimalToBinary(num);
	printf("\n");
}

int main(void)
{
	test0();
	return 0;
}