#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ����һ��int�����Լ�һ��Ŀ��ֵ��
   ���д�����ҵ����Ŀ��ֵ���±꣬Ҫ��ú���û�з���ֵ��
*/

void findLabel(int* nums, int len, int target, int* result) {
	for (int i = 0; i < len; ++i) {
		if (nums[i] == target) {
			*result = i;
			return;
		}
	}
	*result = -1;
}

void test0() {
	int nums[] = { 1,2,3,4,999,6,7,8,9,10 };
	int tar = 6;
	int label;
	for (int i = 0; i < 10; ++i) {
		printf("%d ", *(nums + i));
	}
	findLabel(nums, 10, tar, &label);
	printf("\nĿ��ֵ%d���±��ǣ�%d\n", tar, label);
}

int main(void)
{
	test0();
	return 0;
}