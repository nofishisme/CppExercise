//�ж����������Ƿ��෴���š�����1�� - 2�;����෴�ķ���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool judgeTwoIntegersSign(int x, int y) {
	return (x & 0x80000000) ^ (y & 0x80000000);
}

void test0() {
	int num1,num2;
	printf("�������һ��������\n");
	scanf("%d", &num1);
	printf("������ڶ���������\n");
	scanf("%d", &num2);
	if (judgeTwoIntegersSign(num1, num2)) {
		printf("%d �� %d ���෴�ķ���",num1,num2);
	}
	else {
		printf("%d �� %d ������ͬ",num1,num2);
	}
}

int main(void)
{
	test0();
	return 0;
}