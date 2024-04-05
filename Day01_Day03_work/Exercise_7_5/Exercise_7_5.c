#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int findOneTimeElem(int arr[], int n) {
	if (n == 1)
		return arr[0];
	int elem = arr[0];
	for (int i = 1; i < n; ++i) {
		elem ^= arr[i];
	}
	return elem;
}

void test0() {
	int arr[] = { 0,0,1,1,2,2,4,5,6,4,6,7,7 };
	int result;
	result = findOneTimeElem(arr, 13);
	for (int i = 0; i < 13; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	printf("只出现一次的元素是：%d", result);
}

int main(void)
{
	test0();
	return 0;
}