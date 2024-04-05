//编写一个函数，计算一个整数的二进制表示中1的个数。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int countOnesNumInInt(int num) {
	int count = 0,bitMask = 1;
	int pos = 0;
	while (pos < 32) {
		if ((num & bitMask) != 0) {
			count++;
		}
		bitMask <<= 1;
		pos++;
	}
	return count;
}

void test0() {
	int num;
	printf("请输入一个整数：\n");
	scanf("%d", &num);
	printf("%d 中1的个数是：%d", num, countOnesNumInInt(num));
}

int main(void)
{
	test0();
	return 0;
}