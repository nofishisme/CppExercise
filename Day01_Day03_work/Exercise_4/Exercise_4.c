//����ѭ����������������е�ˮ�ɻ�������ͳ���ܹ��м�������ν��ˮ�ɻ�����ָһ����λ�������λ���ֵ������͵��ڸ�������
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
	printf("ˮ�ɻ����ĸ�����%d\n", daffodiCount);
}

void test0() {
	daffodilNumber();
}

int main(void)
{
	test0();
	return 0;
}