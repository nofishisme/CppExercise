#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

int myCompareOfStringByLength(void* str1, void* str2) {
	char* string1 = *(char**)str1;
	char* string2 = *(char**)str2;
	//�ӳ�����������ô����������Ϊ������Ӧ�÷��ظ�ֵ
	return -((int)strlen(string1) - (int)strlen(string2));
}

int myCompareOfStringByLengthAndDictionary(void* str1, void* str2) {
	char* string1 = *(char**)str1;
	char* string2 = *(char**)str2;
	int len1 = strlen(string1);
	int len2 = strlen(string2);
	if (len1 != len2) {
		return len1 - len2;
	}
	return strcmp(string1, string2);
}

//ȥ�����з�
void processString(char* string) {
	while (string && *string != '\n') {
		string++;
	}
	if (string) {
		*string = 0;
	}
}

void pringString(char** stringArray, int nums) {
	for (int i = 0; i < nums; i++)
	{
		printf("%s\n", stringArray[i]);
	}
}

void test0() {
	int number_of_string;
	printf("������Ҫ¼����ַ���������");
	scanf("%d", &number_of_string);
	//������������
	while (getchar() != '\n');
	char buff[1024];
	char** stringArray = calloc(number_of_string, sizeof(char*));
	ERROR_INFO(stringArray, NULL, "stringArray calloc error;\n");
	for (int i = 0; i < number_of_string; ++i) {
		printf("������� %d ���ַ�����", i + 1);
		fgets(buff, 1024, stdin);
		//ȥ��ĩβ���з�
		processString(buff);
		stringArray[i] = malloc(strlen(buff) * sizeof(char) + 1);
		ERROR_INFO(stringArray[i], NULL, "stringArray[%d] malloc error.\n", i);
		strcpy(stringArray[i], buff);
	}

	printf("�����ȴӳ���������Ľ��:\n");
	qsort(stringArray, number_of_string, sizeof(char*), myCompareOfStringByLength);
	pringString(stringArray, number_of_string);

	printf("�����ȴӶ̵������򣬳���һ��ʱ�����ֵ�����:\n");
	qsort(stringArray, number_of_string, sizeof(char*), myCompareOfStringByLengthAndDictionary);
	pringString(stringArray, number_of_string);

	//�ͷŶѿռ�
	for (int j = 0; j < number_of_string; j++) {
		free(stringArray[j]);
	}
	free(stringArray);
}

int main(void)
{
	test0();
	return 0;
}