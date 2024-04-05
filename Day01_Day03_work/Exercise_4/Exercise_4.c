//经典循环案例：请求出所有的水仙花数，并统计总共有几个。所谓的水仙花数是指一个三位数，其各位数字的立方和等于该数本身。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void daffodilNumber() {
	int daffodiCount = 0;
	for (int i = 100; i < 1000; ++i) {
		int a = pow(i % 10, 3);
		int b = pow(i / 10 % 10, 3);
		int c = pow(i / 100, 3);
		if (i == a + b + c) {
			printf("%d ", i);
			daffodiCount++;
		}
	}
	printf("\n");
	printf("水仙花数的个数：%d\n", daffodiCount);
}

void test0() {
	daffodilNumber();
}

int main(void)
{
	test0();
	return 0;
}