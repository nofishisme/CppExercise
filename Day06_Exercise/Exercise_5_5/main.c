#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ����һ���ǿ���������src���ٸ���һ���㹻����dest���顣
   ��дһ������ copy_array��ʹ�� *p++ ����������鵽һ���µ����顣
   ע�⣺�����ĿҪ�Ѵ���д�þ�����࣡��
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