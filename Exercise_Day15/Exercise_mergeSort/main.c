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

/* 归并排序的实现
*/

void merge(int* nums, int low, int mid, int high, int* buff) {
	int pos = low;
	int low1 = low;
	int low2 = mid + 1;
	while (low1 <= mid && low2 <= high) {
		if (nums[low1] <= nums[low2]) {
			buff[pos++] = nums[low1++];
		}
		else {
			buff[pos++] = nums[low2++];
		}
	}
	while (low1 <= mid) {
		buff[pos++] = nums[low1++];
	}
	while (low2 <= high) {
		buff[pos++] = nums[low2++];
	}
	for (int i = low; i <= high; ++i) {
		nums[i] = buff[i];
	}
}

void divide_merge(int nums[], int low, int high,int* buff){
	if (low >= high) {
		return;
	}
	int mid = low + (high - low >> 1);
	divide_merge(nums, low, mid, buff);
	divide_merge(nums, mid + 1, high, buff);
	merge(nums, low, mid, high, buff);
}

void mergeSort(int nums[], int n) {
	int* buff = malloc(n * sizeof(int));
	if (!buff) {
		printf("mergeSort malloc error.\n");
	}
	divide_merge(nums, 0, n - 1, buff);
	free(buff);
}

void printfArray(int* nums, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

void test0() {
	int nums[] = { 8, 3, 2, 6, 9, 7, 1, 0, 4, 5 };
	printfArray(nums, 10);
	mergeSort(nums, 10);
	printfArray(nums, 10);
}

int main(void)
{
	test0();
	return 0;
}