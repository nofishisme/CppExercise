#define _CRT_SECURE_NO_WARNINGS
#include "DynamicArrayStack.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* 在任意以往自己实现的栈的基础上，编写代码完成括号的匹配。
*  括号有三类：{}、[]、()
*  注：
*  1.若字符串中没有括号，也算做匹配成功。
*/

bool bracketMatch(char* str) {
	Stack* st = stack_create();
	while (*str) {
		switch (*str)
		{
		case '{':
		case '[':
		case '(':
			stack_push(st, *str);
			break;
		case '}':
			if (is_empty(st) || stack_peek(st) != '{') {
				return false;
			}
			stack_pop(st);
			break;
		case ']':
			if (is_empty(st) || stack_peek(st) != '[') {
				return false;
			}
			stack_pop(st);
			break;
		case ')':
			if (is_empty(st) || stack_peek(st) != '(') {
				return false;
			}
			stack_pop(st);
			break;
		default:
			break;
		}
		str++;
	}
	if (is_empty(st)) {
		return true;
	}
	return false;
}

void test0() {
	char str[256];
	printf("输入一个字符串进行括号匹配：\n");
	fgets(str, 256, stdin);
	bracketMatch(str) ? printf("括号匹配正确") : printf("括号匹配失败");
}

int main(void)
{
	test0();
	return 0;
}