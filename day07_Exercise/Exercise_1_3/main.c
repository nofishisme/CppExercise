#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��д�Լ���C���Կ⺯����
   char *my_strncpy(char *dest, const char *src, size_t n);
*/

char* my_strncpy(char* dest, const char* src, size_t n) {
	char* tmp = dest;
	while (n&& n-- && (*dest++ = *src++));
	while (n--)
	{
		*dest++ = 0;
	}
	return tmp;
}

void test0() {
	char* str = "nofish";
	char dest[64];
	my_strncpy(dest, str,4);
	printf("�ַ��� str �ǣ�%s\n", str);
	printf("�ַ��� dest �ǣ�%s\n", dest);
}

int main(void)
{
	test0();
	return 0;
}