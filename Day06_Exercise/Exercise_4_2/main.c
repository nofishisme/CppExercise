#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��ƽ��ֵ������һ��double���飬��ƽ��ֵ�����ҷ��ء�

   Ҫ��ʹ��whileѭ���������飬Ȼ�����"*p++"���﷨ʵ�֡�

   �������������£�

   double get_ave(double *arr, int len); 
*/

double get_ave(double* arr, int len);

void test0() {
	double nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	for (int i = 0; i < 10; ++i) {
		printf("%.2lf ", *(nums + i));
	}
	printf("\n����ƽ��ֵ�ǣ�%.2lf\n", get_ave(nums,10));
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