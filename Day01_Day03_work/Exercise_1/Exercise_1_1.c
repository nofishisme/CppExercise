#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void test0() {
	int Chinese, Math, English;
	double average;
	printf("请输入语文成绩：");
	scanf("%d", &Chinese);
	printf("请输入数学成绩：");
	scanf("%d", &Math);
	printf("请输入英语成绩：");
	scanf("%d", &English);
	average = (Chinese + Math + English) / 3;
	printf("平均成绩是：%.2lf\n", average);
}

int main(void)
{
	test0();
	return 0;
}