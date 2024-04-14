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
	//从长到短排序，那么如果长度相减为正数，应该返回负值
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

//去除换行符
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
	printf("请输入要录入的字符串数量：");
	scanf("%d", &number_of_string);
	//消除多余输入
	while (getchar() != '\n');
	char buff[1024];
	char** stringArray = calloc(number_of_string, sizeof(char*));
	ERROR_INFO(stringArray, NULL, "stringArray calloc error;\n");
	for (int i = 0; i < number_of_string; ++i) {
		printf("请输入第 %d 个字符串：", i + 1);
		fgets(buff, 1024, stdin);
		//去除末尾换行符
		processString(buff);
		stringArray[i] = malloc(strlen(buff) * sizeof(char) + 1);
		ERROR_INFO(stringArray[i], NULL, "stringArray[%d] malloc error.\n", i);
		strcpy(stringArray[i], buff);
	}

	printf("按长度从长到短排序的结果:\n");
	qsort(stringArray, number_of_string, sizeof(char*), myCompareOfStringByLength);
	pringString(stringArray, number_of_string);

	printf("按长度从短到长排序，长度一致时按照字典排序:\n");
	qsort(stringArray, number_of_string, sizeof(char*), myCompareOfStringByLengthAndDictionary);
	pringString(stringArray, number_of_string);

	//释放堆空间
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