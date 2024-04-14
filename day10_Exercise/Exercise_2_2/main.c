#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct stundent_s {
	int number;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
} Student;

void printInfo(const Student*);

void average(Student*, double*, double* b, double*);

void test0() {
	Student stu[5];
	double ave_chinese, ave_math, ave_english;
	for (int i = 0; i < 5; i++) {
		printf("请输入第 %d 个学生数据：学号 姓名 性别(m/f) 语文分数 数学分数 英语分数 \n", i + 1);
		scanf("%d %s %c %d %d %d", &stu[i].number, stu[i].name, &stu[i].gender,
			&stu[i].chinese, &stu[i].math, &stu[i].english);
	}
	for (int i = 0; i < 5; ++i) {
		printInfo(&stu[i]);
		printf("\n");
	}
	average(stu, &ave_chinese, &ave_math, &ave_english);
	printf("平均成绩：\n");
	printf("chinese: %.2lf\n", ave_chinese);
	printf("math: %.2lf\n", ave_math);
	printf("english: %.2lf\n", ave_english);
}


int main(void)
{
	test0();
	return 0;
}

void printInfo(const Student* stu) {
	printf("number: %d\n", stu->number);
	printf("name: %s\n", stu->name);
	printf("gender: %c\n", stu->gender);
	printf("chinese: %d\n", stu->chinese);
	printf("math: %d\n", stu->math);
	printf("english: %d\n", stu->english);
}

void average(Student* stu, double* a, double* b, double* c) {
	double sum_a = 0, sum_b = 0, sum_c = 0;
	for (int i = 0; i < 5; ++i) {
		sum_a += stu[i].chinese;
		sum_b += stu[i].math;
		sum_c += stu[i].english;
	}
	*a = sum_a / 5;
	*b = sum_b / 5;
	*c = sum_c / 5;
}