#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ����ṹ�����͵ı������ڴ沼���������ģ���ʹ��VS��Debugģʽ�鿴�����ڴ沼��
*  �ṹ�����������ͳ�ʼ��
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