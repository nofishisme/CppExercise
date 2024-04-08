#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/* ��ŵ������
   ������ֽ⣬��N�����Ӵ�A������B����Ϊ��ת�ŵ�C���ӣ���ô����Ҫ�Ȱ������N-1����������A������C����Ϊ��ת�ŵ�B���ӣ�
   Ȼ���ٽ�A���ӵ��Ǹ��������ӷ���C�����ϡ�
   ��ʱN-1�����Ӿ���B�������ˣ���ʱ�ͱ���ˣ���Ҫ��B�ϵ�N-1��������AΪ��תվ���ŵ�C���ӡ�
   �������N�Ĺ�ģ�����N-1�Ĺ�ģ���Դ����ƣ�ֱ��ֻʣ��һ�����ӡ�
*/

void Hanoi(int n, char A, char B, char C) {
	if (n == 1) {
		printf("%c-->%c\n", A, C);
		return;
	}
	//�Ƚ�A��n-1�����ӷ���B��
	Hanoi(n - 1, A, C, B);
	//��A������µ������Ǹ����ӷ���C��
	printf("%c-->%c\n", A, C);
	//��B��n-1������ת�Ƶ�C��
	Hanoi(n - 1, B, A, C);
}

void test0() {
	int n = 4;
	char first = 'A', buff = 'B', target = 'C';
	int steps = 1;
	for (int i = 0; i < n; ++i) {
		steps *= 2;
	}
	printf("���%d�����ӵĺ�ŵ�����⣬������Ҫ%d����ȫ���ƶ��켣���£�\n",n ,steps - 1);
	Hanoi(n, first, buff, target);
}

int main(void)
{
	test0();
	return 0;
}