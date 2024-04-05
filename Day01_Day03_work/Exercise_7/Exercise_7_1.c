#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void test0() {
	int num;
	printf("请输入一个整数");
	scanf("%d", &num);
	if (num % 2 == 0)
		printf("%d 不是一个奇数\n",num);
	else
		printf("%d 是一个奇数\n",num);
}

int main(void)
{
	test0();
	return 0;
}