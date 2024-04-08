#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 编写一个函数，检查一个整数数组是否是回文，即正序与倒序相同。
   例如[1,2,3,2,1]就是回文的。要求使用指针的算术运算，不要使用取下标运算
*/

bool isPalindrome(int* arr, int len) {
	int* start = arr;
	int* end = arr + len - 1;
	while (start < end) {
		if (*start != *end) {
			return false;
		}
		start++;
		end--;
	}
	return true;
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	printf("nums:\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\nnums 是否是回文数组：%d", isPalindrome(nums, 10));
	int nums2[] = { 1,2,3,4,5,5,4,3,2,1 };
	printf("\nnums2:\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums2 + i));
	}
	printf("\nnums2 是否是回文数组：%d", isPalindrome(nums2, 10));
}

int main(void)
{
	test0();
	return 0;
}