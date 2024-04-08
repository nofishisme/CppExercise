#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// �ж�abc�Ƿ������������Σ�true��ʾ������ɣ�false��ʾ������
bool is_triangle(double a, double b, double c);
// ���ú��׹�ʽ��abc���Թ��������ε�ǰ���£������������
double get_area(double a, double b, double c);


void test0() {
	double edge1, edge2, edge3, area;
	int p;
	printf("�������1�߳���");
	scanf("%lf", &edge1);
	printf("�������2�߳���");
	scanf("%lf", &edge2);
	printf("�������3�߳���");
	scanf("%lf", &edge3);
	while (!is_triangle(edge1, edge2, edge3)) {
		printf("������������߲�����������Σ��������������߱߳�\n");
		printf("�������1�߳���");
		scanf("%lf", &edge1);
		printf("�������2�߳���");
		scanf("%lf", &edge2);
		printf("�������3�߳���");
		scanf("%lf", &edge3);
	}
	area = get_area(edge1, edge2, edge3);
	printf("����������ǣ�%.2lf", area);
}

int main(void)
{
	test0();
	return 0;
}

bool is_triangle(double a, double b, double c) {
	return (a + b > c) && (a + c > b) && (b + c > a);
}

double get_area(double a, double b, double c) {
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}