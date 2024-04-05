#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void printYangHuiTriangle(void) {
	//给杨辉三角数值加入到数组，使用左对齐，大于0的数都是放在数组前边，数组后边的数全为0
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
	//打印杨辉三角
	for (int k = 0; k < 10; k++) {
		//不同行时，打印的前置空格数目不同
		for (int m = 0; m < (10 - k) / 2; m++) {
			printf("    ");
		}
		//打印空格后打印非零的杨辉三角数值
		for (int pos = 0; pos <= k; pos++) {
			printf("%-4d", yangHuiTriangle[k][pos]);
		}
		//打印后置的空格
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