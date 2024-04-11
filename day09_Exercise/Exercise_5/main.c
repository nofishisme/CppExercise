#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
/* 标准库函数strcat会将一个字符串追加到另一个字符串的末尾。
* 现在我们编写一个函数把两个字符串拼接起来，返回拼接的结果，但要求不改变其中任何一个字符串。其函数声明如下：
* char* my_strcat(const char* prefix, const char* suffix);
* 形参prefix表示前缀，suffix表示后缀，拼接的结果是prefix + suffix
* 比如：my_strcat("abc", "d")，拼接的结果是"abcd"。
*/

char* my_strcat(const char* prefix, const char* suffix) {
	char* tmp = malloc(strlen(prefix) + strlen(suffix) + 1);
	char* start = tmp;
	if (!start) {
		fprintf(stderr, "my_strcat malloc error\n");
		return NULL;
	}
	while (*prefix && (*tmp++ = *prefix++));
	while (*suffix && (*tmp++ = *suffix++));
	*tmp = 0;
	return start;
}

void test0() {
	char prefix[] = { "My name is" };
	char suffix[] = { "nofish." };
	char* my_cat = my_strcat(prefix, suffix);

	printf("prefix: %s\n", prefix);
	printf("suffix: %s\n", suffix);
	printf("my_cat: %s\n", my_cat);

	free(my_cat);
}

int main(void)
{
	test0();
	return 0;
}