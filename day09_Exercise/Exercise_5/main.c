#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
 
/* ��׼�⺯��strcat�Ὣһ���ַ���׷�ӵ���һ���ַ�����ĩβ��
* �������Ǳ�дһ�������������ַ���ƴ������������ƴ�ӵĽ������Ҫ�󲻸ı������κ�һ���ַ������亯���������£�
* char* my_strcat(const char* prefix, const char* suffix);
* �β�prefix��ʾǰ׺��suffix��ʾ��׺��ƴ�ӵĽ����prefix + suffix
* ���磺my_strcat("abc", "d")��ƴ�ӵĽ����"abcd"��
*/

char* my_strcat(const char* prefix, const char* suffix) {
	char* tmp = malloc(strlen(prefix) + strlen(suffix) + 1);
	char* start = tmp;
	if (!start) {
		fprintf(stderr, "my_strcat malloc error\n");
		return NULL;
	}
	while (*prefix && (*tmp++ = *prefix++));
	while (*suffix && (*tmp++ = *suffix++));
	*tmp = 0;
	return start;
}

void test0() {
	char prefix[] = { "My name is" };
	char suffix[] = { "nofish." };
	char* my_cat = my_strcat(prefix, suffix);

	printf("prefix: %s\n", prefix);
	printf("suffix: %s\n", suffix);
	printf("my_cat: %s\n", my_cat);

	free(my_cat);
}

int main(void)
{
	test0();
	return 0;
}