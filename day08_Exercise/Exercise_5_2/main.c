#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* void delete_character(char* str, char c);
*/

void delete_character(char* str, char c) {
	char* new_end = str, * pos = str;//˫ָ��˼�룬�滻����ɾ��
	while (*pos) {
		if (*pos == c) {
			pos++;
		}
		else {
			*new_end = *pos;
			new_end++;
			pos++;
		}
	}
	*new_end = 0;//����ɾ������ĩβҪ�Կ��ַ�����
}

void test0() {
	char str[255] = { "abcdaefaghiagkl" };
	printf("ɾ�� 'a' ǰ��%s\n", str);
	delete_character(str,'a');
	printf("ɾ�� 'a' ��%s\n", str);
}

int main(void)
{
	test0();
	return 0;
}