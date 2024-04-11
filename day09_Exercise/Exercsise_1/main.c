#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

/* 编写函数，查找一个int数组中的最大元素和第二大元素，
*  并将它们分别存放在由 largest 和 second_largest 指向的变量中。
*  按照下面的函数声明来实现这个函数。
*  void find_two_largest(int arr[], int n, int* largest, int* second_largest);
*/

void find_two_largest(int arr[], int n, int* largest, int* second_largest) {
	*largest = INT_MIN;
	*second_largest = INT_MIN;
	int* end = arr + n;
	while (arr < end) {
		if (*arr > *largest) {
			*largest = *arr;
		}
		arr++;
	}
	arr = end - n;
	while (arr < end) {
		if (*arr > *second_largest && *arr != *largest) {
			*second_largest = *arr;
		}
		arr++;
	}
}

void test0() {
	int arr[] = { 1,2,3,4,5,6,7,8,9,11,333 };
	int largest = 0, second_largest = 0;
	for (int i = 0; i < 11; i++) {
		printf("%d ", *(arr + i));
	}
	printf("\n");
	find_two_largest(arr, 11, &largest, &second_largest);
	printf("最大值和第二大值分别是：%d %d\n", largest, second_largest);
}

int main(void)
{
	test0();
	return 0;
}