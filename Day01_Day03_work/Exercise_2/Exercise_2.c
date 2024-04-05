#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

void numberAndLetterCount() {
	char arr[255];
	int pos = 0, digCount = 0, letterCount = 0;
	printf("请输入一行字符：\n");
	scanf("%s", arr);
	while (arr[pos]) {
		if (isdigit(arr[pos]))
			digCount++;
		else if (isalpha(arr[pos]))
			letterCount++;
		pos++;
	}
	printf("数字的数目是：%d个", digCount);
	printf("字母的数目是：%d个", letterCount);
}

void test0() {
	numberAndLetterCount();
}

int main(void)
{
	test0();
	return 0;
}