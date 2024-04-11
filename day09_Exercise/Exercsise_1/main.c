#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

/* ��д����������һ��int�����е����Ԫ�غ͵ڶ���Ԫ�أ�
*  �������Ƿֱ������� largest �� second_largest ָ��ı����С�
*  ��������ĺ���������ʵ�����������
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
	printf("���ֵ�͵ڶ���ֵ�ֱ��ǣ�%d %d\n", largest, second_largest);
}

int main(void)
{
	test0();
	return 0;
}