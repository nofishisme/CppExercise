#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��дһ�����������һ�����������Ƿ��ǻ��ģ��������뵹����ͬ��
   ����[1,2,3,2,1]���ǻ��ĵġ�Ҫ��ʹ��ָ����������㣬��Ҫʹ��ȡ�±�����
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
	printf("\nnums �Ƿ��ǻ������飺%d", isPalindrome(nums, 10));
	int nums2[] = { 1,2,3,4,5,5,4,3,2,1 };
	printf("\nnums2:\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums2 + i));
	}
	printf("\nnums2 �Ƿ��ǻ������飺%d", isPalindrome(nums2, 10));
}

int main(void)
{
	test0();
	return 0;
}