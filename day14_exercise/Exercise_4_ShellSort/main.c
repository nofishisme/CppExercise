#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* 请手动实现希尔排序:
*  void shell_sort(int nums[], int n);
*/

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//希尔排序，增量初始为5，每次缩小一半
void shell_sort(int nums[], int n) {
	int increment = 5;
	for (; increment > 0; increment >>= 1) {
		for (int i = increment; i < n; ++i) {
			int j = i;
			while (j > increment - 1) {
				if (nums[j] < nums[j - increment]) {
					swap(nums + j, nums + j - increment);
					j = j - increment;
				}
				else {
					break;
				}
			}
		}
	}
}

void printArray(int* nums, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

void test0() {
	printf("希尔排序：\n");
	int nums[] = { 22,33,1,44,5,6,7,99,23,24,65,77,88 };
	printArray(nums, 13);
	shell_sort(nums, 13);
	printArray(nums, 13);
}

int main(void)
{
	test0();
	return 0;
}