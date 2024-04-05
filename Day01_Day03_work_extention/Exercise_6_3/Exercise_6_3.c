//利用位运算符求一个整数的绝对值
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int abs(int num) {
	return num >= 0 ? num : (~num + 1);
}

void test0() {
	int num;
	printf("请输入一个整数：\n");
	scanf("%d", &num);
	printf("%d 的绝对值是：%d", num ,abs(num));
}

int main(void)
{
	test0();
	return 0;
}