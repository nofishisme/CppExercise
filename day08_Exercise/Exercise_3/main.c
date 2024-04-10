#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��дһ�����������������ַ����е�Բ����()�Ƿ���ȷƥ�䡣
*  ע��ֻ����С���ţ��ַ�����û���������š�
*  ���ַ�����((Hello) (World))
*  �����᷵��һ������ֵ����ʾƥ��ɹ���ʧ��
*  ע�⣺ֻ����Ӣ������
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
	printf("������һ���ַ�����\n");
	char str[256];
	fgets(str, 256, stdin);
	printf("�ַ����Ƿ�ƥ����ȷ��");
	bracketMatch(str) ? printf("��\n") : printf("��\n");
}

int main(void)
{
	test0();
	return 0;
}