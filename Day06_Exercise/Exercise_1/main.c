//����һ������ʽ��������Ҫ�������ύ��������Ӽ��˳���
// �����ڽ�������ʱ����ӡ�ܹ�ִ�в����Ĵ�������Ҳ������Щ�������õĴ�����
//������ʵ�֣�Ҫ���жϳ�����Ϊ0�������ڳ���Ϊ0ʱʹ��exit��ʾ�쳣�˳����̡�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

//�ӷ�
int add(int a, int b);
//����
int substract(int a, int b);
//�˷�
int multiplay(int a, int b);
//����
double divide(int a, int b);
//��ȡ�����ֵ
void getValue(int* a, int* b, char* computeSign);
//����
void compute(int a, int b, char computeSign, int* count);

void calculator(void) {
	int a, b, count = 0;
	char computeSign;
	char ch;
	do {
		printf("������Ҫ����ı��ʽ(���磬5 + 3)��");
		getValue(&a, &b, &computeSign);
		compute(a, b, computeSign, &count);
		printf("�Ƿ������(y/n)��");
		while (isspace(ch = getchar()));//�����հ��ַ�
		while (getchar() != '\n');//���������ַ�
		printf("\n");
	} while (ch == 'y' || ch == 'Y');
	printf("�ܹ�ִ�еĲ��������ǣ�%d\n", count);
}


void test0() {
	calculator();
}

int main(void)
{
	test0();
	return 0;
}

int add(int a, int b) {
	return a + b;
}

int substract(int a, int b) {
	return a - b;
}

int multiplay(int a, int b) {
	return a * b;
}

double divide(int a, int b) {
	if (b == 0) {
		exit(EXIT_FAILURE);
	}
	return (double)a / b;
}

void getValue(int* a, int* b, char* computeSign) {
	*a = 0;
	*b = 0;
	char input;//��ǰ�����ַ�
	int pos = 0;//�Ƿ��Ѿ������������
	while ((input = getchar()) != '\n') {
		if (input == '+' || input == '-' || input == '*' || input == '/' && pos == 0) {
			*computeSign = input;
			pos++;
		}
		else if (isdigit(input) && pos == 0) {
			*a = *a * 10 + input - '0';
		}
		else if (isdigit(input) && pos == 1) {
			*b = *b * 10 + input - '0';
		}
	}
}

void compute(int a, int b, char computeSign, int* count) {
	switch (computeSign)
	{
	case '+':
		printf("�����%d\n", add(a, b));
		(*count)++;
		break;
	case '-':
		printf("�����%d\n", substract(a, b));
		(*count)++;
		break;
	case '*':
		printf("�����%d\n", multiplay(a, b));
		(*count)++;
		break;
	case '/':
		printf("�����%.2lf\n", divide(a, b));
		(*count)++;
		break;
	default:
		printf("��Ч�������\n");
		break;
	}
}