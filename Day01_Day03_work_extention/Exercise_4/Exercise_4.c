#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool judgeIsLeapYear(int year);//判断是否是闰年
int calculateDistance(int year, int month, int day);//计算和基准日期1970/1/1的天数距离
void getdate(char* date, int* year, int* month, int* day);//从输入的字符串日期提取数字日期

void calculateWeek() {
	char* week[] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wednesday" };
	char date[64];
	printf("请输入一个日期（xxxx/xxxx/xxxx）：\n");
	scanf("%s", date);
	int year = 0, month = 0, day = 0;
	getdate(date, &year, &month, &day);
	int distance = calculateDistance(year, month, day);
	printf("%s 是 %s", date, week[distance % 7]);
}

void test0() {
	calculateWeek();
}

int main(void)
{
	test0();
	return 0;
}

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

int calculateDistance(int year, int month, int day) {
	int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int distance = 0;
	//计算除开year年的天数
	for (int i = 1970; i < year; ++i) {
		if (judgeIsLeapYear(i)) {
			distance += 366;
		}
		else {
			distance += 365;
		}
	}
	//累加year年，month月之前的天数
	//如果是闰年，2月天数加1
	if (judgeIsLeapYear(year)) {
		monthDays[1] = 29;
	}
	for (int j = 0; j < month - 1 && j < 11; ++j) {
		distance += monthDays[j];
	}
	//累加month月的天数
	distance += day;
	distance--;//因为多计算了1970/1/1日这一天
	return distance;
}

void getdate(char* date, int* year, int* month, int* day) {
	int flag = 0;
	//读取year，month，day
	for (int i = 0; date[i]; ++i) {
		if (isdigit(date[i]) && flag == 0) {
			*year = *year * 10 + date[i] - '0';
		}
		else if (isdigit(date[i]) && flag == 1) {
			*month = *month * 10 + date[i] - '0';
		}
		else if (isdigit(date[i]) && flag == 2) {
			*day = *day * 10 + date[i] - '0';
		}
		else if (date[i] == '/' && flag == 0) {
			flag = 1;
		}
		else if (date[i] == '/' && flag == 1) {
			flag = 2;
		}
	}
}