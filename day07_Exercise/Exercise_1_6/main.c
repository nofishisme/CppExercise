#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��д�Լ���C���Կ⺯����
   int my_strcmp(const char *str1, const char *str2);
*/

int my_strcmp(const char* str1, const char* str2) {
	//��*str1��*str2����һ����Ϊ0ʱ�����ܼ�����ǰ�жϣ�����Ϊ0��������ַ����Ѿ�����
	while ((*str1 || *str2) && *str1++ == *str2++);
	if (*--str1 == *--str2) {
		return 0;
	}
	return *str1 > *str2 ? 1 : -1;
}

void test0() {
	char* str1 = "nofish";
	char* str2 = "nofish";
	printf("�ַ��� str1 �ǣ�%s\n", str1);
	printf("�ַ��� str2 �ǣ�%s\n", str2);
	printf("�ַ��� str1 ���ַ��� str2 �Ƿ���ͬ��%d", my_strcmp(str1,str2));
}

int main(void)
{
	test0();
	return 0;
}