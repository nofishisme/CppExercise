#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 编写函数交换数组中两个下标的元素。
   要求不能使用[]运算符且函数声明如下：void swap(int *arr, int i, int j) 
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
	printf("\n交换下标为4和5的元素之后：\n");
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