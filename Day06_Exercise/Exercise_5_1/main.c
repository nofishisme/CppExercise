#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 数组元素的逆序。要求使用指针操作直接完成，不要使用下标运算。
*/

void swapTwoNum(int* a, int* b);

void reverse(int* arr, int len) {
	int* start = arr;
	int* end = arr + len - 1;
	while (start < end) {
		swapTwoNum(start, end);
		start++;
		end--;
	}
}

void swapTwoNum(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	printf("数组逆置之前：\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\n数组逆置之后：\n");
	reverse(nums, 10);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
}

int main(void)
{
	test0();
	return 0;
}