//制作一个交互式计算器，要求至少提交四种运算加减乘除，
// 并且在结束进程时，打印总共执行操作的次数。（也就是这些函数调用的次数）
//除法的实现，要求判断除数不为0，并且在除数为0时使用exit表示异常退出进程。
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

//加法
int add(int a, int b);
//减法
int substract(int a, int b);
//乘法
int multiplay(int a, int b);
//除法
double divide(int a, int b);
//获取输入的值
void getValue(int* a, int* b, char* computeSign);
//计算
void compute(int a, int b, char computeSign, int* count);

void calculator(void) {
	int a, b, count = 0;
	char computeSign;
	char ch;
	do {
		printf("请输入要计算的表达式(例如，5 + 3)：");
		getValue(&a, &b, &computeSign);
		compute(a, b, computeSign, &count);
		printf("是否继续？(y/n)：");
		while (isspace(ch = getchar()));//跳过空白字符
		while (getchar() != '\n');//跳过多余字符
		printf("\n");
	} while (ch == 'y' || ch == 'Y');
	printf("总共执行的操作次数是：%d\n", count);
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
	char input;//当前输入字符
	int pos = 0;//是否已经输入了运算符
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
		printf("结果：%d\n", add(a, b));
		(*count)++;
		break;
	case '-':
		printf("结果：%d\n", substract(a, b));
		(*count)++;
		break;
	case '*':
		printf("结果：%d\n", multiplay(a, b));
		(*count)++;
		break;
	case '/':
		printf("结果：%.2lf\n", divide(a, b));
		(*count)++;
		break;
	default:
		printf("无效的运算符\n");
		break;
	}
}