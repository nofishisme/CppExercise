#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 给定一个非空整数数组src，再给定一个足够长的dest数组。
   编写一个函数 copy_array，使用 *p++ 复制这个数组到一个新的数组。
   注意：这道题目要把代码写得尽量简洁！！
*/

void copy_array(int* dest, int* src, int len) {
	int* pos = src;
	int* end = src + len;
	while (pos < end) {
		*dest++ = *pos++;
	}
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	printf("nums:\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	int dest[64];
	printf("\ndest:\n");
	copy_array(dest, nums, 10);
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(dest + i));
	}
}

int main(void)
{
	test0();
	return 0;
}