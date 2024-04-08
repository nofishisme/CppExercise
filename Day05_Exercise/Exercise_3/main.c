#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

// 判断abc是否可以组成三角形，true表示可以组成，false表示不可以
bool is_triangle(double a, double b, double c);
// 利用海伦公式在abc可以构成三角形的前提下，求三角形面积
double get_area(double a, double b, double c);


void test0() {
	double edge1, edge2, edge3, area;
	int p;
	printf("请输入边1边长：");
	scanf("%lf", &edge1);
	printf("请输入边2边长：");
	scanf("%lf", &edge2);
	printf("请输入边3边长：");
	scanf("%lf", &edge3);
	while (!is_triangle(edge1, edge2, edge3)) {
		printf("错误，输入的三边不能组成三角形，请重新输入三边边长\n");
		printf("请输入边1边长：");
		scanf("%lf", &edge1);
		printf("请输入边2边长：");
		scanf("%lf", &edge2);
		printf("请输入边3边长：");
		scanf("%lf", &edge3);
	}
	area = get_area(edge1, edge2, edge3);
	printf("三角形面积是：%.2lf", area);
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