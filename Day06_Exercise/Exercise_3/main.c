#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��ŵ������
   ������ֽ⣬��N�����Ӵ�A������B����Ϊ��ת�ŵ�C���ӣ���ô����Ҫ�Ȱ������N-1����������A������C����Ϊ��ת�ŵ�B���ӣ�
   Ȼ���ٽ�A���ӵ��Ǹ��������ӷ���C�����ϡ�
   ��ʱN-1�����Ӿ���B�������ˣ���ʱ�ͱ���ˣ���Ҫ��B�ϵ�N-1��������AΪ��תվ���ŵ�C���ӡ�
   �������N�Ĺ�ģ�����N-1�Ĺ�ģ���Դ����ƣ�ֱ��ֻʣ��һ�����ӡ�

   ��չ
   ����n�����ӵĺ�ŵ�����⣬����һ������m��Ҫ���ڿ���̨��ӡ��m + 1�����ƶ��켣��
*/

void Hanoi(int n, char A, char B, char C, int* count, int m) {
	//�Ѿ�������Ŀ�경�����˳�����
	if ((*count) >= (m + 1))
		return;
	if (n == 1) {
		//��Ч��һ�������в���ͳ��
		(*count)++;
		if ((*count) == (m + 1)) {
			printf("%c --> %c\n", A, C);
		}
		return;
	}
	Hanoi(n - 1, A, C, B, count, m);
	//��Ч��һ�������в���ͳ��
	(*count)++;
	if ((*count) == (m + 1)) {
		printf("%c --> %c\n", A, C);
		return;
	}
	Hanoi(n - 1, B, A, C, count, m);
}

void playHanoigame(int nums, int step) {
	char first = 'A', buff = 'B', m = 'C';
	int count = 0;
	printf("%d�����ӵĺ�ŵ�����⣬��%d�����ƶ��켣�ǣ�", nums, step + 1);
	Hanoi(nums, first, buff, m, &count, step);
}

void test0() {
	playHanoigame(2, 2);
	playHanoigame(3, 2);
	playHanoigame(4, 10);
}

int main(void)
{
	test0();
	return 0;
}