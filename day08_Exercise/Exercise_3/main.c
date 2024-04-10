#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 编写一个函数，检查给定的字符串中的圆括号()是否正确匹配。
*  注意只考虑小括号，字符串中没有其它括号。
*  如字符串：((Hello) (World))
*  函数会返回一个布尔值，表示匹配成功或失败
*  注意：只考虑英文括号
*/

bool bracketMatch(char* str) {
	char stack[64];
	int top = -1;
	while (*str) {
		switch (*str)
		{
		case '(':
			stack[++top] = *str;
			break;
		case ')':
			if (top == -1) {
				return false;
			}
			stack[top--];
			break;
		default:
			break;
		}
		str++;
	}
	return -1 == top ? true : false;
}

void test0() {
	printf("请输入一串字符串：\n");
	char str[256];
	fgets(str, 256, stdin);
	printf("字符串是否匹配正确：");
	bracketMatch(str) ? printf("是\n") : printf("否\n");
}

int main(void)
{
	test0();
	return 0;
}