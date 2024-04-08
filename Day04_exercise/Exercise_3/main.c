#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define YANG_HUI_NUMS 10

void printYangHuiTriangle(void) {
	//给杨辉三角数值加入到数组，使用左对齐，大于0的数都是放在数组前边，数组后边的数全为0
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
	//打印杨辉三角
	for (int k = 0; k < YANG_HUI_NUMS; k++) {
		//不同行时，打印的前置空格数目不同，保证每行杨辉三角的元素都是居中的
		for (int m = 0; m < (YANG_HUI_NUMS - k) / 2; m++) {
			//如果是奇数行，每行就少打两个空格，保证奇数行和奇数行对齐，偶数行和偶数行对齐
			if (k % 2 == 0 && m == 0) {
				printf("  ");
			}
			else {
				printf("    ");
			}
		}
		//打印空格后打印非零的杨辉三角数值，第k行有k个非零的杨辉三角值。
		for (int pos = 0; pos <= k; pos++) {
			printf("%-4d", yangHuiTriangle[k][pos]);
		}
		//打印后置的空格（这里其实没必要，不影响显示效果）
#if 0
		for (int n = (YANG_HUI_NUMS - k) / 2; n < YANG_HUI_NUMS; n++) {
			printf("    ");
		}
#endif
		//换行必须要
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