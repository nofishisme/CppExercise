#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

/* 查找数组的最大值和最小值，但要将最大值作为返回值返回，最小值则依靠传入的指针完成赋值。

	要求不能使用"[]"运算符。

	函数的声明如下：

	int max_min(int *arr, int len, int *pmin);
*/

int max_min(int* arr, int len, int* pmin);

void test0() {
	int nums[] = { 1,2,3,44,55,666,777,888,9876,22,0,33,-1 };
	int max, min;
	max = max_min(nums, 13, &min);
	for (int i = 0; i < 13; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\n数组最大值是：%d ，最小值是：%d\n", max, min);
}

int main(void)
{
	test0();
	return 0;
}

int max_min(int* arr, int len, int* pmin) {
	int minNum = INT_MAX, maxNum = INT_MIN;
	int pos = 0;
	while (pos < len) {
		if (*(arr + pos) > maxNum) {
			maxNum = *(arr + pos);
		}
		else if (*(arr + pos) < minNum) {
			minNum = *(arr + pos);
		}
		pos++;
	}
	*pmin = minNum;
	return maxNum;
}