#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 编写自己的C语言库函数：
   int my_strcmp(const char *str1, const char *str2);
*/

int my_strcmp(const char* str1, const char* str2) {
	//当*str1和*str2其中一个不为0时，才能继续向前判断，若都为0，则表明字符串已经结束
	while ((*str1 || *str2) && *str1++ == *str2++);
	if (*--str1 == *--str2) {
		return 0;
	}
	return *str1 > *str2 ? 1 : -1;
}

void test0() {
	char* str1 = "nofish";
	char* str2 = "nofish";
	printf("字符串 str1 是：%s\n", str1);
	printf("字符串 str2 是：%s\n", str2);
	printf("字符串 str1 和字符串 str2 是否相同：%d", my_strcmp(str1,str2));
}

int main(void)
{
	test0();
	return 0;
}