#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ���д���������ַ����е���ĸ�����ַֿ���
*  ʹ���ַ�����ǰһ���������֣���һ��������ĸ��
*  void seperate(char* str);
*  ����: "h1ell2o3"
*  ���: "123hello"��������������ǰ����ĸ�ں���ַ���
*  ע�⣺Ҫ���ַ���ֻ������ĸ�����֣��ַ����ĳ��Ȳ�����100��
*  �ҷ���Ҫ������ԭ��������ɡ�
*/

void swap(char* a, char* b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void seperate(char* str) {
	char* start = str;
	while (*str++);
	char* end = str - 2;
	while (start < end) {
		if (isdigit(*start)) {
			start++;
		}
		else {
			swap(start, end);
			end--;
		}
	}
}

void test0() {
	//printf("������һ���ַ�����\n");
	char str[256] = {"h1ell2o3"};
	//scanf("%s", str);
	printf("��ĸ���ַֿ���\n");
	seperate(str);
	printf("%s", str);
}

int main(void)
{
	test0();
	return 0;
}