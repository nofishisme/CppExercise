#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(int* a, int* b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
void test0() {
	int a, b;
	printf("�����һ�����֣�");
	scanf("%d", &a);
	printf("����ڶ������֣�");
	scanf("%d", &b);
	printf("������������ǰ��\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);
	printf("�����������ֺ�\n");
	swap(&a, &b);
	printf("a: %d\n", a);
	printf("b: %d\n", b);
}

int main(void)
{
	test0();
	return 0;
}