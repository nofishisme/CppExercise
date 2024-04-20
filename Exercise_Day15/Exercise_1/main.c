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

/* 请实现快速排序，并分析它的时间复杂度，空间复杂度和稳定性。需要用单/双向分区来实现
 * void quick_sort(int arr[], int n);​
*/

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

//单向分区
int single_partition(int* arr, int low, int high) {
	int pivot = arr[high];
	int idx = low;
	for (int i = low; i < high; ++i) {
		if (arr[i] < pivot) {
			swap(arr + idx, arr + i);
			idx++;
		}
	}
	swap(arr + idx, arr + high);
	return idx;
}

//双向分区
int partition(int arr[], int low, int high) {
	int pivot = arr[low];
	while (low < high) {
		while (low < high && arr[high] > pivot) {
			high--;
		}
		arr[low] = arr[high];
		while (low < high && arr[low] < pivot) {
			low++;
		}
		arr[high] = arr[low];
	}
	arr[low] = pivot;
	return low;
}

void partitionSort(int arr[], int low, int high) {
	if (low < high) {
		int pivot_num = single_partition(arr, low, high);
		partitionSort(arr, low, pivot_num - 1);
		partitionSort(arr, pivot_num + 1, high);
	}
}

void quick_sort(int arr[], int n) {
	partitionSort(arr, 0, n - 1);
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
	printf("快速排序后：\n");
	quick_sort(nums, 10);
	printfArray(nums, 10);
}

int main(void)
{
	test0();
	return 0;
}