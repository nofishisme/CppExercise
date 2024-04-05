//给定一个非空的整数数组nums，已知有两个元素只出现了一次，其余元素均出现两次，那么请你找出这两个只出现一次的元素。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void findTwoSingleElem(int arr[], int n) {
	int bitmask = 0,elem1 = 0, elem2 = 0;
	for (int i = 0; i < n; ++i) {
		bitmask ^= arr[i];
	}
	int diff = bitmask & (-bitmask);
	for (int j = 0; j < n; ++j) {
		if (arr[j] & diff != 0)//这里核心就是说，避开所求2个数元素其中一个元素，然后和数组中其他元素进行异或，最后得到一个所求2个元素中的另一个。
			elem1 ^= arr[j];
	}
	elem2 = bitmask ^ elem1;
	printf("第一个元素是：%d\n", elem1);
	printf("第二个元素是：%d\n", elem2);
}

void test0() {
	int nums[] = { 1,1,2,2,3,9,3,9,8,8,7,6,5,5 };
	for (int i = 0; i < 14; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
	findTwoSingleElem(nums, 14);
}

int main(void)
{
	test0();
	return 0;
}