#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ����Ԫ�ص�����Ҫ��ʹ��ָ�����ֱ����ɣ���Ҫʹ���±����㡣
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
	printf("��������֮ǰ��\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\n��������֮��\n");
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