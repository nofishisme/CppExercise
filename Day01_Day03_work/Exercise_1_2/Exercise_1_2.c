#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test0() {
	double num;
	printf("����һ��(0,1)�����֣�\n");
	scanf("%lf", &num);
	num *= 100;
	printf("%.1lf%%", num);
}

int main(void)
{
	test0();
	return 0;
}