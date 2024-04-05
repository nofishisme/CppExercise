#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


void rateCalculate(void) {
	int rate;
	int rewardYears;
	double principal = 100;
	printf("请输入年利率：");
	scanf("%d", &rate);
	printf("请输入要投资的年份：");
	scanf("%d", &rewardYears);
	//创建一个数组用来存储每年5个不同利率下的余额,初始本金余额是100
	double balances[5] = { 100,100,100,100,100 };
	printf("\n\n");
	printf("Years         ");
	for (int i = 0; i < rewardYears; ++i) {
		printf("%3d%%  ",rate + i);//格式化打印
		if (i != rewardYears - 1) {
			printf("     ");
		}
		else {
			printf("\n");
		}
	}
	for (int j = 0; j < rewardYears; ++j) {//打印每过一年不同利率下余额
		printf("%4d          ",j + 1);
		for (int k = 0; k < 5; ++k) {
			balances[k] = balances[k] + balances[k] * (rate + k) / 100;//计算不同利率下的余额
			printf("%.2lf", balances[k]);
			if (k != 4) {//如果不是最后
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