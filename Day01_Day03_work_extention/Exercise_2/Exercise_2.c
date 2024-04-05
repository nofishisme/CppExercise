#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

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

void theNextDay() {
	char date[64];
	printf("请输入一个日期（xxxx/xxxx/xxxx）：\n");
	scanf("%s", date);
	int year = 0, month = 0, day = 0;
	int flag = 0;
	//读取year，month，day
	for (int i = 0; date[i]; ++i) {
		if (isdigit(date[i]) && flag == 0) {
			year = year * 10 + date[i] - '0';
		}
		else if (isdigit(date[i]) && flag == 1) {
			month = month * 10 + date[i] - '0';
		}
		else if (isdigit(date[i]) && flag == 2) {
			day = day * 10 + date[i] - '0';
		}
		else if (date[i] == '/' && flag == 0) {
			flag = 1;
		}
		else if (date[i] == '/' && flag == 1) {
			flag = 2;
		}
	}
	//判断平年闰年然后写出每月天数
	int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (judgeIsLeapYear(year)) {
		monthDays[1] = 29;
	}
	//计算下一天
	day++;
	if (month > 0 && day > monthDays[month - 1]) {
		day = day - monthDays[month - 1];
		month++;
		if (month > 12) {
			month = month - 12;
			year++;
		}
	}
	printf("%d年%d月%d日\n", year, month, day);
}

void test0() {
	theNextDay();
}

int main(void)
{
	test0();
	return 0;
}