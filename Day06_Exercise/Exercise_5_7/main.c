#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 给定一个整数数组，将所有奇数移到数组前面，
   偶数移到数组后面。（扩展题）
*/

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void oddBeforeEven(int* nums, int len) {
	int* start = nums;
	int* end = nums + len - 1;
	while (start < end) {
		if (*start % 2 == 1) {
			start++;
		}
		else {
			swap(start, end);
			end--;
		}
	}
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	printf("Before processing:\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\nAfter processing:\n");
	oddBeforeEven(nums, 10);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
}

int main(void)
{
	test0();
	return 0;
}