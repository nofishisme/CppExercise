#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/* ���ַ����еĿո��滻�� %020 (�ٶ�ԭ�ַ������ܹ�����滻����ַ���)��
*/

void substitute_space(char* str) {
	char* start = str, * end, * pos;
	int length = strlen(str);
	int count = 0;
	pos = start + length;//posָ��ԭ�ַ���ĩβ
	while (*str) {
		if (*str == ' ') {
			count++;
		}
		str++;
	}
	end = start + length + count * 3;//�µ��ַ����������ĩβ
	while (end > start) {
		if (*pos != ' ') {
			*end = *pos;
			end--;
			pos--;
		}
		else {
			*end-- = '0';
			*end-- = '2';
			*end-- = '0';
			*end-- = '%';
			pos--;
		}
	}
}

void test0() {
	char str[255] = { "hello world how " };
	printf("�滻ǰ��%s\n", str);
	substitute_space(str);
	printf("�滻��%s\n", str);
}

int main(void)
{
	test0();
	return 0;
}