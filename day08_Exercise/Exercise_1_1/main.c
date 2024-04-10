#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/*
* 给定一个字符串，要求它可能包含数字和字母。
* 请编写函数，统计该字符串中每个字符出现的次数，
* 统计过程中忽略大小写的差异，并打印最终每个字符出现的次数。
*/
//使用36个元素的int数组存储每个字符或者数字出现次数，
// 该宏定义为对应字符在数组中多出的偏置值
#define OFFSET_OF_NUM 48//数字存在数组的0 - 9号下标，所以需要减去偏置值48
#define OFFSET_OF_UPPER 55//数组下标10 - 35，大写字母偏置值55
#define OFFSET_OF_LOWER 87//数组下标10 - 35，小写字面偏置值87

void statisticalCharacters() {
	printf("请输入一串字符串：\n");
	int store[36];
	for (int i = 0; i < 36; ++i) {
		store[i] = 0;
	}
	char ch;
	while ((ch = getchar()) != '\n') {
		if (isdigit(ch)) {
			store[ch - OFFSET_OF_NUM]++;
		}
		else if (isalpha(ch)) {
			isupper(ch) ? store[ch - OFFSET_OF_UPPER]++ : store[ch - OFFSET_OF_LOWER]++;
		}
	}
	for (int i = 0; i < 10; ++i) {
		if (store[i] != 0) {
			printf("%c : %d\n", i + OFFSET_OF_NUM, store[i]);
		}
	}
	for (int j = 10; j < 36; ++j) {
		if (store[j] != 0) {
			printf("%c : %d\n", j + OFFSET_OF_UPPER, store[j]);
		}
	}
}

void test0() {
	statisticalCharacters();
}

int main(void)
{
	test0();
	return 0;
}