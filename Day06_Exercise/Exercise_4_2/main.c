#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 求平均值，给定一个double数组，求平均值，并且返回。

   要求使用while循环遍历数组，然后配合"*p++"的语法实现。

   函数的声明如下：

   double get_ave(double *arr, int len); 
*/

double get_ave(double* arr, int len);

void test0() {
	double nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	for (int i = 0; i < 10; ++i) {
		printf("%.2lf ", *(nums + i));
	}
	printf("\n数组平均值是：%.2lf\n", get_ave(nums,10));
}

int main(void)
{
	test0();
	return 0;
}

double get_ave(double* arr, int len) {
	double* end = arr + len;
	double sum = 0;
	while (arr < end) {
		sum += *arr++;
	}
	return sum / len;
}