#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test0() {
	int num,temp;
	printf("请输入一个整数");
	scanf("%d", &num);
	temp = num;
	while (temp % 2 == 0)
		temp /= 2;
	if (temp == 1)
		printf("%d 是2的幂", num);
	else
		printf("%d 不是2的幂", num);
}

int main(void)
{
	test0();
	return 0;
}