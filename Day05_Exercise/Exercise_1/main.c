#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

/* 4�ֻ�ɫ��ʹ��һ�������ĸ��ַ����������洢
   13�ֵ�����ʹ��һ���˰���13���ַ����������洢
   �������ʹ�õ������
   ÿ�η���֮���Ƶ�����Ӧ��Ҫ��һ�ţ���Ӧ�÷��ظ�����
   ʹ��һ����ά�������洢ÿ�����Ƿ��Ѿ�������
*/
void distributeCards() {
	int nums = 0;//��Ҫ����������
	//��ʼ����ɫ����
	char suit[4] = { 'C','D','H','S' };
	//��ʼ����������
	char point[13] = { '2','3','4,','5','6','7','8','9','T','J','Q','K','A' };
	int exist[4][13];
	//��ʼ�����Ƽ�¼����
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			exist[i][j] = 0;
		}
	}
	srand(time(NULL));
	printf("����������Ҫ������������\n");
	scanf("%d", &nums);
	//����
	printf("������.");
	Sleep(500);
	printf("\b..");
	Sleep(500);
	printf("\b\b...");
	Sleep(500);
	printf("\b\b\b....");
	Sleep(500);
	printf("\r");
	printf("���������ǣ�\n");
	for (int k = 0; k < nums; k++) {
		int s = rand() % 4;
		int p = rand() % 13;//�������ɫ�͵���
		while (exist[s][p] == 1) {
			s = rand() % 4;//�Ѿ�������ͬ��ɫ�ˣ��������µ������ɫ�͵���
			p = rand() % 13;
		}
		exist[s][p] = 1;
		printf("%c%c      ", suit[s], point[p]);
	}
}
void test0() {
	distributeCards();
}

int main(void)
{
	test0();
	return 0;
}