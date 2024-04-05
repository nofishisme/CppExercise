#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool judgeIsLeapYear(int year) {
	if (0 != year % 4) {
		return false;
	}
	else if (0 != year % 100) {
		return true;
	}
	else if (0 != year % 400) {
		return false;
	}
	else {
		return true;
	}
}

void test0() {
	int year;
	printf("请输入一个年份：\n");
	scanf("%d", &year);
	while (year > 0) {
		if (judgeIsLeapYear(year)) {
			printf("%d 是闰年\n",year);
		}
		else {
			printf("%d 是平年\n",year);
		}
		printf("请输入一个年份：\n");
		scanf("%d", &year);
	}
}

int main(void)
{
	test0();
	return 0;
}