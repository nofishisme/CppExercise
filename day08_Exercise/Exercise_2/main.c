#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 编写一个函数，计算一个字符串中单词的数量。这里，单词被定义为由空格分隔的字符序列。
* 例如，对于字符串"hello world! word Excel space blank"
* 就应该输出有6个单词
*/

int countWords(char* str) {
	int count = 0;
	while (*str) {
		while (isspace(*str)) {
			str++;
		}
		//空白符结束，那么下一个肯定是单词
		if (*str) {
			count++;
		}
		while (*str && !isspace(*str)) {
			str++;
		}
	}
	return count;
}

void test0() {
	printf("请输入一串字符串：\n");
	char str[256];
	fgets(str, 256, stdin);
	printf("单词数目是：%d\n", countWords(str));
}

int main(void)
{
	test0();
	return 0;
}