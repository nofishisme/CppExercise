#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* ��дһ������������һ���ַ����е��ʵ�������������ʱ�����Ϊ�ɿո�ָ����ַ����С�
* ���磬�����ַ���"hello world! word Excel space blank"
* ��Ӧ�������6������
*/

int countWords(char* str) {
	int count = 0;
	while (*str) {
		while (isspace(*str)) {
			str++;
		}
		//�հ׷���������ô��һ���϶��ǵ���
		if (*str) {
			count++;
		}
		while (*str && !isspace(*str)) {
			str++;
		}
	}
	return count;
}

void test0() {
	printf("������һ���ַ�����\n");
	char str[256];
	fgets(str, 256, stdin);
	printf("������Ŀ�ǣ�%d\n", countWords(str));
}

int main(void)
{
	test0();
	return 0;
}