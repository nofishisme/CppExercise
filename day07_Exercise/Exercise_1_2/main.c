#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��д�Լ���C���Կ⺯����
   char *my_strcpy(char *dest, const char *src);
*/

char* my_strcpy(char* dest, const char* src) {
	char* tmp = dest;
	while (*dest++ = *src++);
	return tmp;
}

void test0() {
	char* str = "nofish";
	char dest[64];
	my_strcpy(dest, str);
	printf("�ַ��� str �ǣ�%s\n", str);
	printf("�ַ��� dest �ǣ�%s\n", dest);
}

int main(void)
{
	test0();
	return 0;
}