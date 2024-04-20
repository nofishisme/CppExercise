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

/* 请手动实现堆排序
*/

void printfArray(int* nums, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void toBigheap(int* nums, int n, int idx) {
	while (true) {
		int max_idx = idx;
		int lchild_idx = (idx << 1) + 1;
		int rchlid_idx = (idx << 1) + 2;
		if (lchild_idx < n && nums[lchild_idx] > nums[max_idx]) {
			max_idx = lchild_idx;
		}
		if (rchlid_idx < n && nums[rchlid_idx] > nums[max_idx]) {
			max_idx = rchlid_idx;
		}
		if (max_idx != idx) {
			swap(nums + idx, nums + max_idx);
			idx = max_idx;
		}
		else {
			break;
		}
	}
}

void createBigHeap(int* nums, int heap_len) {
	int last_idx = (heap_len - 2) >> 1;
	for (int i = last_idx; i >= 0; --i) {
		toBigheap(nums, heap_len, i);
	}
}

void heap_sort(int* nums, int heap_len) {
	createBigHeap(nums, heap_len);
	int pos = heap_len - 1;
	while (pos > 0) {
		swap(nums, nums + pos);
		toBigheap(nums, pos, 0);
		pos--;
	}
}



void test0() {
	int nums[] = { 8, 3, 2, 6, 9, 7, 1, 0, 4, 5 };
	printfArray(nums, 10);
	printf("堆排序后：\n");
	heap_sort(nums, 10);
	printfArray(nums, 10);
}

int main(void)
{
	test0();
	return 0;
}