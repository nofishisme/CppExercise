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

/* �����ö��ֲ���ʵ��:
*  1.�������������һ����Ŀ��ֵ��ȵ�Ԫ��
*  2.�������һ��С�ڵ���Ŀ��ֵ��Ԫ��
*  3.�Ľ���������
*/

//1.�������������һ����Ŀ��ֵ��ȵ�Ԫ��
int findTheLastElemByBinarySearch(int nums[], int n, int target) {
	int low = 0, high = n - 1,mid = low + (high - low >> 1);
	int idx = -1;
	while (low < high) {
		if (nums[mid] == target) {
			idx = mid;
			low = mid + 1;
		}
		else if (nums[mid] < target) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
		mid = low + (high - low >> 1);
	}
	return idx;
}

//2.�������һ��С�ڵ���Ŀ��ֵ��Ԫ��
int findTheLastLessthanElem(int nums[], int n, int target) {
	int low = 0, high = n - 1, mid = low + (high - low >> 1);
	while (low < high) {
		if (nums[mid] > target) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
			if (nums[low] > target) {
				return mid;
			}
		}
		mid = low + (high - low >> 1);
	}
}

//3.�Ľ���������

// ���ֲ��ң������������в��Ҳ���λ��
int binary_search(int arr[], int item, int start, int end) {
	if (start == end) {
		return (arr[start] > item) ? start : start + 1;
	}
	if (start > end) {
		return start;
	}

	int mid = start + (end - start >> 1);
	if (arr[mid] < item) {
		return binary_search(arr, item, mid + 1, end);
	}
	else if (arr[mid] > item) {
		return binary_search(arr, item, start, mid - 1);
	}
	else {
		return mid;
	}
}

void insertSort(int* nums, int n) {
	for (int i = 1; i < n; i++) {
		int key = nums[i];
		int insert_index = binary_search(nums, key, 0, i - 1);

		// ��Ԫ������ƶ�
		for (int j = i; j > insert_index; j--) {
			nums[j] = nums[j - 1];
		}
		nums[insert_index] = key;
	}
}


void printfArray(int* nums, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

void test0() {
	int nums[] = { 1,2,3,3,4,4,5,5,8,8,9,9,9,11,13,15,15 };
	int nums2[] = { 3,4,2,1,44,4,2,3,4,55,6,7,9,8 };
	int len = sizeof(nums) / sizeof(nums[0]);
	int len2 = sizeof(nums2) / sizeof(nums2[0]);
	printfArray(nums, len);
	printf("��������9�����һ�����Ԫ���±��ǣ�%d\n", findTheLastElemByBinarySearch(nums, len, 9));
	printf("�������һ��С�ڵ�������6Ԫ���±��ǣ�%d\n", findTheLastLessthanElem(nums, len, 6));
	printf("�����ǸĽ���Ĳ�������:\n");
	printfArray(nums2, len2);
	insertSort(nums2, len2);
	printfArray(nums2, len2);
}

int main(void)
{
	test0();
	return 0;
}