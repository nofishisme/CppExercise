#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ±àÐ´×Ô¼ºµÄCÓïÑÔ¿âº¯Êý£º
   char *my_strcat(char *dest, const char *src);
*/

char* my_strcat(char* dest, const char* src) {
	char* tmp = dest;
	while (*++dest);
	while (*dest++ = *src++);
	return tmp;
}

void test0() {
	char* str = "nofish";
	char dest[64] = "My name is";
	printf("×Ö·û´® str ÊÇ£º%s\n", str);
	printf("×Ö·û´® dest ÊÇ£º%s\n", dest);
	my_strcat(dest, str);
	printf("Æ´½Óºó£¬×Ö·û´® dest ÊÇ£º%s\n", dest);
}

int main(void)
{
	test0();
	return 0;
}