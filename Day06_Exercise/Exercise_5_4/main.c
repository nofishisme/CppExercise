#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��д�������������������±��Ԫ�ء�
   Ҫ����ʹ��[]������Һ����������£�void swap(int *arr, int i, int j) 
*/

void swap(int* arr, int i, int j) {
	int temp = *(arr + i);
	*(arr + i) = *(arr + j);
	*(arr + j) = temp;
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\n�����±�Ϊ4��5��Ԫ��֮��\n");
	swap(nums, 4, 5);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	printf("\n");
}

int main(void)
{
	test0();
	return 0;
}