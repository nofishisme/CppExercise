#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


void rateCalculate(void) {
	int rate;
	int rewardYears;
	double principal = 100;
	printf("�����������ʣ�");
	scanf("%d", &rate);
	printf("������ҪͶ�ʵ���ݣ�");
	scanf("%d", &rewardYears);
	//����һ�����������洢ÿ��5����ͬ�����µ����,��ʼ���������100
	double balances[5] = { 100,100,100,100,100 };
	printf("\n\n");
	printf("Years         ");
	for (int i = 0; i < rewardYears; ++i) {
		printf("%3d%%  ",rate + i);//��ʽ����ӡ
		if (i != rewardYears - 1) {
			printf("     ");
		}
		else {
			printf("\n");
		}
	}
	for (int j = 0; j < rewardYears; ++j) {//��ӡÿ��һ�겻ͬ���������
		printf("%4d          ",j + 1);
		for (int k = 0; k < 5; ++k) {
			balances[k] = balances[k] + balances[k] * (rate + k) / 100;//���㲻ͬ�����µ����
			printf("%.2lf", balances[k]);
			if (k != 4) {//����������
				printf("     ");
			}
			else {
				printf("\n");
			}
		}
	}
}

void test0(void) {
	rateCalculate();
}

int main(void)
{
	test0();
	return 0;
}