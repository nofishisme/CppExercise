//����λ�������һ�������ľ���ֵ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int abs(int num) {
	return num >= 0 ? num : (~num + 1);
}

void test0() {
	int num;
	printf("������һ��������\n");
	scanf("%d", &num);
	printf("%d �ľ���ֵ�ǣ�%d", num ,abs(num));
}

int main(void)
{
	test0();
	return 0;
}