#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


void test0() {
	int num;
	printf("������һ������");
	scanf("%d", &num);
	if (num % 2 == 0)
		printf("%d ����һ������\n",num);
	else
		printf("%d ��һ������\n",num);
}

int main(void)
{
	test0();
	return 0;
}