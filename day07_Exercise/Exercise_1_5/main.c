#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ��д�Լ���C���Կ⺯����
   char *my_strncat(char *dest, const char *src, size_t n);
*/

char* my_strncat(char* dest, const char* src, size_t n) {
	char* tmp = dest;
	while (*++dest);//�ҵ���ƴ�������ĩβ���ַ���
	while (n && n-- && (*dest++ = *src++));
	*--dest = 0;
	return tmp;
}

void test0() {
	char* str = "nofish";
	char dest[64] = "My name is\0hhhhhhhhhh";
	printf("�ַ��� str �ǣ�%s\n", str);
	printf("�ַ��� dest �ǣ�%s\n", dest);
	my_strncat(dest, str,sizeof(dest) - strlen(str) - 1);
	printf("ƴ�Ӻ��ַ��� dest �ǣ�%s\n", dest);
}

int main(void)
{
	test0();
	return 0;
}