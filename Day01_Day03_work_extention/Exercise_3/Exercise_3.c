#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool judgeIsLeapYear(int year);//判断是否是闰年
void getdate(char* date, int* year, int* month, int* day);//从输入的字符串日期提取数字日期
int calculateDistance(int year, int month, int day);//计算和基准日期1/1/1的天数距离

void twoDateDistance(void) {
	char date1[64],date2[64];
	printf("请输入第一个日期（xxxx/xxxx/xxxx）：\n");
	scanf("%s", date1);
	printf("请输入第二个日期（xxxx/xxxx/xxxx）：\n");
	scanf("%s", date2);
	int year1 = 0, month1 = 0, day1 = 0;
	int year2 = 0, month2 = 0, day2 = 0;
	int distance;
	//读取year1，month1，day1
	getdate(date1, &year1, &month1, &day1);
	//读取year2，month2，day2
	getdate(date2, &year2, &month2, &day2);
	distance = calculateDistance(year2, month2, day2) - calculateDistance(year1, month1, day1);
	printf("%s 和 %s 间隔 %d 天", date1, date2, distance);
}

void test0() {
	twoDateDistance();
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

int calculateDistance(int year, int month, int day) {
	int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int distance = 0;
	//计算除开year年的天数
	for (int i = 1; i < year; ++i) {
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
	return distance;
}