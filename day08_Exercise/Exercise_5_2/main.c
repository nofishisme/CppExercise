#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* void delete_character(char* str, char c);
*/

void delete_character(char* str, char c) {
	char* new_end = str, * pos = str;//双指针思想，替换代替删除
	while (*pos) {
		if (*pos == c) {
			pos++;
		}
		else {
			*new_end = *pos;
			new_end++;
			pos++;
		}
	}
	*new_end = 0;//覆盖删除后，新末尾要以空字符结束
}

void test0() {
	char str[255] = { "abcdaefaghiagkl" };
	printf("删除 'a' 前：%s\n", str);
	delete_character(str,'a');
	printf("删除 'a' 后：%s\n", str);
}

int main(void)
{
	test0();
	return 0;
}