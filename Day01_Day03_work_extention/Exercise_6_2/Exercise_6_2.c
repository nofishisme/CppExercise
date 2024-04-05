//判断两个整数是否相反符号。比如1和 - 2就具有相反的符号
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool judgeTwoIntegersSign(int x, int y) {
	return (x & 0x80000000) ^ (y & 0x80000000);
}

void test0() {
	int num1,num2;
	printf("请输入第一个整数：\n");
	scanf("%d", &num1);
	printf("请输入第二个整数：\n");
	scanf("%d", &num2);
	if (judgeTwoIntegersSign(num1, num2)) {
		printf("%d 和 %d 有相反的符号",num1,num2);
	}
	else {
		printf("%d 和 %d 符号相同",num1,num2);
	}
}

int main(void)
{
	test0();
	return 0;
}