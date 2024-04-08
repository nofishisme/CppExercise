#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 数组元素求和。要求使用`*p++`来完成数组元素的累加 
*/

int sum(int* nums, int len) {
	int total = 0;
	int* start = nums;
	int* end = nums + len;
	while (start < end) {
		total += *start++;
	}
	return total;
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\n数组的和是：%d\n",sum(nums,10));
}

int main(void)
{
	test0();
	return 0;
}