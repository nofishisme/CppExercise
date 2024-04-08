#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define YANG_HUI_NUMS 10

void printYangHuiTriangle(void) {
	//�����������ֵ���뵽���飬ʹ������룬����0�������Ƿ�������ǰ�ߣ������ߵ���ȫΪ0
	int yangHuiTriangle[YANG_HUI_NUMS][YANG_HUI_NUMS];
	for (int i = 0; i < YANG_HUI_NUMS; ++i) {
		for (int j = 0; j < YANG_HUI_NUMS; j++) {
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
	for (int k = 0; k < YANG_HUI_NUMS; k++) {
		//��ͬ��ʱ����ӡ��ǰ�ÿո���Ŀ��ͬ����֤ÿ��������ǵ�Ԫ�ض��Ǿ��е�
		for (int m = 0; m < (YANG_HUI_NUMS - k) / 2; m++) {
			//����������У�ÿ�о��ٴ������ո񣬱�֤�����к������ж��룬ż���к�ż���ж���
			if (k % 2 == 0 && m == 0) {
				printf("  ");
			}
			else {
				printf("    ");
			}
		}
		//��ӡ�ո���ӡ��������������ֵ����k����k��������������ֵ��
		for (int pos = 0; pos <= k; pos++) {
			printf("%-4d", yangHuiTriangle[k][pos]);
		}
		//��ӡ���õĿո�������ʵû��Ҫ����Ӱ����ʾЧ����
#if 0
		for (int n = (YANG_HUI_NUMS - k) / 2; n < YANG_HUI_NUMS; n++) {
			printf("    ");
		}
#endif
		//���б���Ҫ
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