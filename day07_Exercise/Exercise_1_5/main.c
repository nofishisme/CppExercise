#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* 编写自己的C语言库函数：
   char *my_strncat(char *dest, const char *src, size_t n);
*/

char* my_strncat(char* dest, const char* src, size_t n) {
	char* tmp = dest;
	while (*++dest);//找到被拼接数组的末尾空字符；
	while (n && n-- && (*dest++ = *src++));
	*--dest = 0;
	return tmp;
}

void test0() {
	char* str = "nofish";
	char dest[64] = "My name is\0hhhhhhhhhh";
	printf("字符串 str 是：%s\n", str);
	printf("字符串 dest 是：%s\n", dest);
	my_strncat(dest, str,sizeof(dest) - strlen(str) - 1);
	printf("拼接后，字符串 dest 是：%s\n", dest);
}

int main(void)
{
	test0();
	return 0;
}