#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 请编写函数，将字符串中的字母和数字分开，
*  使得字符串中前一部分是数字，后一部分是字母。
*  void seperate(char* str);
*  输入: "h1ell2o3"
*  结果: "123hello"或者任意数字在前，字母在后的字符串
*  注意：要求字符串只包含字母和数字，字符串的长度不超过100，
*  且分组要最终在原数组上完成。
*/

void swap(char* a, char* b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void seperate(char* str) {
	char* start = str;
	while (*str++);
	char* end = str - 2;
	while (start < end) {
		if (isdigit(*start)) {
			start++;
		}
		else {
			swap(start, end);
			end--;
		}
	}
}

void test0() {
	//printf("请输入一串字符串：\n");
	char str[256] = {"h1ell2o3"};
	//scanf("%s", str);
	printf("字母数字分开后：\n");
	seperate(str);
	printf("%s", str);
}

int main(void)
{
	test0();
	return 0;
}