#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 下面结构体类型的变量的内存布局是怎样的？请使用VS的Debug模式查看它的内存布局
*  结构体对象的声明和初始化
*  Student s1 = { 1, "Jack", 'm', 100, 100, 100 };
*/

typedef struct stundent_s {
	int number;
	char name[25];
	char gender;
	int chinese;
	int math;
	int english;
} Student;

void test0() {
	Student s1 = { 1, "Jack", 'm', 100, 100, 100 };
	Student* p = &s1;

}

int main(void)
{
	test0();
	return 0;
}