//дһ������ʵ�ַ�����ӡ��û��Է���/��ĸ����ʽ��������������ӡ��Ӻ�Ľ��(��Ϊ������)��
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

void twoFractionPlus() {
	char fraction1[64], fraction2[64];
	int numerator1 = 0, numerator2 = 0, denominator1 = 0, denominator2 = 0;//����1������2����ĸ1����ĸ2��
	int result_numerator, result_denominator;
	printf("�����һ��������");
	scanf("%s", fraction1);
	printf("����ڶ���������");
	scanf("%s", fraction2);
	int line = 0;//���ӷ�ĸ�ֽ���
	//��ȡ��һ������
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
	printf("��һ��������%d/%d\n", numerator1, denominator1);
	line = 0;
	//��ȡ�ڶ�������
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
	printf("�ڶ���������%d/%d\n", numerator2, denominator2);
	result_numerator = numerator1 * denominator2 + numerator2 * denominator1;
	result_denominator = denominator1 * denominator2;
	//�����Լ�������з�����Լ��
	int pre = result_denominator > result_numerator ? result_denominator : result_numerator;//�ϴ��Ǹ���
	int cur = result_denominator < result_numerator ? result_denominator : result_numerator;//��С�Ǹ���
	//ŷ����÷�����õĹ�Լ������pre
	while (cur != 0) {
		int temp = pre % cur;
		pre = cur;
		cur = temp;
	}
	result_denominator /= pre;
	result_numerator /= pre;
	printf("��������ӽ��Ϊ %d/%d\n", result_numerator, result_denominator);
}

void test0() {
	twoFractionPlus();
}

int main(void)
{
	test0();
	return 0;
}