#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test0() {
	int Chinese, Math, English;
	double average;
	printf("���������ĳɼ���");
	scanf("%d", &Chinese);
	printf("��������ѧ�ɼ���");
	scanf("%d", &Math);
	printf("������Ӣ��ɼ���");
	scanf("%d", &English);
	average = (Chinese + Math + English) / 3;
	printf("ƽ���ɼ��ǣ�%.2lf\n", average);
}

int main(void)
{
	test0();
	return 0;
}