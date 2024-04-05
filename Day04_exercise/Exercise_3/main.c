#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void printYangHuiTriangle(void) {
	//�����������ֵ���뵽���飬ʹ������룬����0�������Ƿ�������ǰ�ߣ������ߵ���ȫΪ0
	int yangHuiTriangle[10][10];
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; j++) {
			if (j > i) {
				yangHuiTriangle[i][j] = 0;
				continue;
			}
			if (j == 0) {
				yangHuiTriangle[i][j] = 1;
			}
			else {
				yangHuiTriangle[i][j] = yangHuiTriangle[i - 1][j] + yangHuiTriangle[i - 1][j - 1];
			}
		}
	}
	//��ӡ�������
	for (int k = 0; k < 10; k++) {
		//��ͬ��ʱ����ӡ��ǰ�ÿո���Ŀ��ͬ
		for (int m = 0; m < (10 - k) / 2; m++) {
			printf("    ");
		}
		//��ӡ�ո���ӡ��������������ֵ
		for (int pos = 0; pos <= k; pos++) {
			printf("%-4d", yangHuiTriangle[k][pos]);
		}
		//��ӡ���õĿո�
		for (int n = (10 - k) / 2; n < 10; n++) {
			printf("    ");
		}
		printf("\n");
	}
}

void test0(void) {
	printYangHuiTriangle();
}

int main(void)
{
	test0();
	return 0;
}