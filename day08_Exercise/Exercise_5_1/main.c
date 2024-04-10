#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/* 将字符串中的空格替换成 %020 (假定原字符数组能够存放替换后的字符串)。
*/

void substitute_space(char* str) {
	char* start = str, * end, * pos;
	int length = strlen(str);
	int count = 0;
	pos = start + length;//pos指向原字符串末尾
	while (*str) {
		if (*str == ' ') {
			count++;
		}
		str++;
	}
	end = start + length + count * 3;//新的字符串在数组的末尾
	while (end > start) {
		if (*pos != ' ') {
			*end = *pos;
			end--;
			pos--;
		}
		else {
			*end-- = '0';
			*end-- = '2';
			*end-- = '0';
			*end-- = '%';
			pos--;
		}
	}
}

void test0() {
	char str[255] = { "hello world how " };
	printf("替换前：%s\n", str);
	substitute_space(str);
	printf("替换后：%s\n", str);
}

int main(void)
{
	test0();
	return 0;
}