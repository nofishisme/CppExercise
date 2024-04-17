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

/* �����������Լ�ʵ�ֵ�ջ�Ļ����ϣ���д����������ŵ�ƥ�䡣
*  ���������ࣺ{}��[]��()
*  ע��
*  1.���ַ�����û�����ţ�Ҳ����ƥ��ɹ���
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
	printf("����һ���ַ�����������ƥ�䣺\n");
	fgets(str, 256, stdin);
	bracketMatch(str) ? printf("����ƥ����ȷ") : printf("����ƥ��ʧ��");
}

int main(void)
{
	test0();
	return 0;
}