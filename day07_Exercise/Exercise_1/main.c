#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 编写自己的C语言库函数：
   size_t my_strlen(const char *str);
*/

size_t my_strlen(const char* str) {
	char* tmp = str;
	while (*++str);
	return str - tmp;
}

void test0() {
	char* str = "My name is nofish";
	int length = my_strlen(str);
	printf("字符串 %s 的长度是：%d\n", str, length);
}

int main(void)
{
	test0();
	return 0;
}