#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test0() {
	int num,temp;
	printf("������һ������");
	scanf("%d", &num);
	temp = num;
	while (temp % 2 == 0)
		temp /= 2;
	if (temp == 1)
		printf("%d ��2����", num);
	else
		printf("%d ����2����", num);
}

int main(void)
{
	test0();
	return 0;
}