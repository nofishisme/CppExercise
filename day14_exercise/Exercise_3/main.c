#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* 请自己手动实现三个基础的排序算法：
*  选择排序
*  冒泡排序
*  插入排序
*/

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//选择排序
void selectSort(int* nums, int n) {
	int min, pos;
	for (int i = 0; i < n - 1; ++i) {
		min = nums[i];
		pos = i;
		for (int j = i + 1; j < n; j++) {
			if (nums[j] < min) {
				min = nums[j];
				pos = j;
			}
		}
		swap(nums + i, nums + pos);
	}
}

//冒泡排序
void bubbleSort(int* nums, int n) {
	bool flag = false;
	for (int i = 0; i < n - 1; ++i) {
		flag = false;
		for (int j = n - 1; j > i; --j) {
			if (nums[j] < nums[j - 1]) {
				swap(nums + j, nums + j - 1);
				flag = true;
			}
		}
		//没发生交换，有序
		if (!flag) {
			return;
		}
	}
}
//插入排序
void insertSort(int* nums, int n) {
	for (int i = 1; i < n; ++i) {
		int j = i;
		while (j > 0) {
			if (nums[j] < nums[j - 1]) {
				swap(nums + j, nums + j - 1);
				j--;
			}
			else {
				break;
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
	printf("选择排序：\n");
	int nums[] = { 22,33,1,44,5,6,7,99,23,24,65,77,88 };
	printArray(nums, 13);
	selectSort(nums, 13);
	printArray(nums, 13);

	printf("冒泡排序：\n");
	int nums1[] = { 122,133,11,144,15,16,17,199,123,124,165,177,188 };
	printArray(nums1, 13);
	bubbleSort(nums1, 13);
	printArray(nums1, 13);

	printf("插入排序：\n");
	int nums2[] = { 1226,1336,116,1446,156,166,176,1996,1236,1246,1656,1776,1886 };
	printArray(nums2, 13);
	insertSort(nums2, 13);
	printArray(nums2, 13);
	
	
}

int main(void)
{
	test0();
	return 0;
}