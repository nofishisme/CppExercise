//��дһ������������һ�������Ķ����Ʊ�ʾ��1�ĸ�����
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
	printf("������һ��������\n");
	scanf("%d", &num);
	printf("%d ��1�ĸ����ǣ�%d", num, countOnesNumInInt(num));
}

int main(void)
{
	test0();
	return 0;
}