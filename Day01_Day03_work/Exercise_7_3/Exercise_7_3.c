#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test0() {
	int num,lsb = 1;
	printf("������һ������");
	scanf("%d", &num);
	while((num & 1) == 0) {
		lsb *= 2;
		num >>= 1;
	}
	printf("LSB�����Чλ����ǣ�%d", lsb);
}

int main(void)
{
	test0();
	return 0;
}