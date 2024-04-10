#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/*
* ����һ���ַ�����Ҫ�������ܰ������ֺ���ĸ��
* ���д������ͳ�Ƹ��ַ�����ÿ���ַ����ֵĴ�����
* ͳ�ƹ����к��Դ�Сд�Ĳ��죬����ӡ����ÿ���ַ����ֵĴ�����
*/
//ʹ��36��Ԫ�ص�int����洢ÿ���ַ��������ֳ��ִ�����
// �ú궨��Ϊ��Ӧ�ַ��������ж����ƫ��ֵ
#define OFFSET_OF_NUM 48//���ִ��������0 - 9���±꣬������Ҫ��ȥƫ��ֵ48
#define OFFSET_OF_UPPER 55//�����±�10 - 35����д��ĸƫ��ֵ55
#define OFFSET_OF_LOWER 87//�����±�10 - 35��Сд����ƫ��ֵ87

void statisticalCharacters() {
	printf("������һ���ַ�����\n");
	int store[36];
	for (int i = 0; i < 36; ++i) {
		store[i] = 0;
	}
	char ch;
	while ((ch = getchar()) != '\n') {
		if (isdigit(ch)) {
			store[ch - OFFSET_OF_NUM]++;
		}
		else if (isalpha(ch)) {
			isupper(ch) ? store[ch - OFFSET_OF_UPPER]++ : store[ch - OFFSET_OF_LOWER]++;
		}
	}
	for (int i = 0; i < 10; ++i) {
		if (store[i] != 0) {
			printf("%c : %d\n", i + OFFSET_OF_NUM, store[i]);
		}
	}
	for (int j = 10; j < 36; ++j) {
		if (store[j] != 0) {
			printf("%c : %d\n", j + OFFSET_OF_UPPER, store[j]);
		}
	}
}

void test0() {
	statisticalCharacters();
}

int main(void)
{
	test0();
	return 0;
}