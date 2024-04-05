//编写一个程序，要求用户键盘录入十名学生的语文成绩(百分制)，然后存储在一个一维数组中。
// 最后计算全班的平均成绩、最高分和最低分，并打印出来。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define STUDENT_NUM 10

void test0() {
	int score[STUDENT_NUM] = { 0 };
	int maxScore = 0, minScore = 100;
	int sum = 0,avrage = 0;
	for (int i = 0; i < STUDENT_NUM; ++i) {
		printf("输入第 %d 个学生的成绩：\n", i + 1);
		scanf("%d", score + i);
		if (score[i] > maxScore) {
			maxScore = score[i];
		}
		if(score[i] < minScore) {
			minScore = score[i];
		}
		sum += score[i];
	}
	avrage = sum / STUDENT_NUM;
	printf("全班最高成绩是：%d\n", maxScore);
	printf("全班最低成绩是：%d\n", minScore);
	printf("全班平均成绩是：%d\n", avrage);
}

int main(void)
{
	test0();
	return 0;
}