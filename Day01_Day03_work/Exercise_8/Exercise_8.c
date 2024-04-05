//写一个程序，实现分数相加。用户以分子/分母的形式输入分数，程序打印相加后的结果(化为最简分数)。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

void twoFractionPlus() {
	char fraction1[64], fraction2[64];
	int numerator1 = 0, numerator2 = 0, denominator1 = 0, denominator2 = 0;//分子1，分子2，分母1，分母2；
	int result_numerator, result_denominator;
	printf("输入第一个分数：");
	scanf("%s", fraction1);
	printf("输入第二个分数：");
	scanf("%s", fraction2);
	int line = 0;//分子分母分界线
	//读取第一个分数
	for (int i = 0; fraction1[i] != '\0'; ++i) {
		if (isdigit(fraction1[i]) && line == 0) {
			numerator1 = numerator1 * 10 + fraction1[i] - '0';
		}
		else if (fraction1[i] == '/') {
			line = 1;
		}
		else if (isdigit(fraction1[i]) && line == 1) {
			denominator1 = denominator1 * 10 + fraction1[i] - '0';
		}
	}
	printf("第一个分数：%d/%d\n", numerator1, denominator1);
	line = 0;
	//读取第二个分数
	for (int i = 0; fraction2[i] != '\0'; ++i) {
		if (isdigit(fraction2[i]) && line == 0) {
			numerator2 = numerator2 * 10 + fraction2[i] - '0';
		}
		else if (fraction2[i] == '/') {
			line = 1;
		}
		else if (isdigit(fraction2[i]) && line == 1) {
			denominator2 = denominator2 * 10 + fraction2[i] - '0';
		}
	}
	printf("第二个分数：%d/%d\n", numerator2, denominator2);
	result_numerator = numerator1 * denominator2 + numerator2 * denominator1;
	result_denominator = denominator1 * denominator2;
	//求最大公约数，进行分数简化约分
	int pre = result_denominator > result_numerator ? result_denominator : result_numerator;//较大那个数
	int cur = result_denominator < result_numerator ? result_denominator : result_numerator;//较小那个数
	//欧几里得方法求得的公约数就是pre
	while (cur != 0) {
		int temp = pre % cur;
		pre = cur;
		cur = temp;
	}
	result_denominator /= pre;
	result_numerator /= pre;
	printf("两分数相加结果为 %d/%d\n", result_numerator, result_denominator);
}

void test0() {
	twoFractionPlus();
}

int main(void)
{
	test0();
	return 0;
}