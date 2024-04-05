#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdbool.h>
#include <ctype.h>

bool judgeIsLeapYear(int year);//判断是否是闰年
int calculateDistance(int year, int month, int day);//计算和基准日期1970/1/1的天数距离
int calculateWeek(int year, int month, int day);//返回当前日期的在weeks中的下标，表示该日期的星期几,weeks数组中存的是万年历对于的星期，其中星期六为第一个元素。

void printCalendar(void) {
	int year;
	char* weeks[] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
	char* months[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	printf("请输入一个年份：\n");
	scanf("%d", &year);
	if (judgeIsLeapYear(year)) {//闰年2月多一天
		monthDays[1] = 29;
	}
	printf("=====================The Calendar of Year %d=====================\n", year);
	int dayToWeek = calculateWeek(year, 1, 1);//该年第一天对应的在weeks中的下标，使用该下标可以在weeks中查到该天是星期几。
	for (int i = 0; i < 12; ++i) {
		printf("%s\n", months[i]);//打印月份
		printf("%s %s %s %s %s %s %s\n", weeks[0], weeks[1], weeks[2], weeks[3], weeks[4], weeks[5], weeks[6]);//打印星期
		for (int j = 0; j < monthDays[i]; ++j,dayToWeek = (dayToWeek + 1) % 7) {//日期是连续的，星期也是连续的，所以dayToWeek只需要每次加1然后对7取模就能求下一个日期的星期下标。
			if (j == 0) {//表明这是该月第一天，开启了新的一页日历，该日期对于前面需要留白
				for (int k = 0; k < dayToWeek; ++k) {//不确定第一天是星期几，但每一天的留白空格符是设定3个再加上一个间隔用的空白符一共四个空白符，要求星期一到这一天之间的位置留白。
					printf("    ");
				}
			}
			printf("%3d", j + 1);//打印日期，3行占位。
			if (dayToWeek == 6) {
				printf("\n");//如果是星期六,需要换行
			}
			else {
				printf(" ");//如果不是星期六，需要加空格字符进行间隔
			}
		}
		printf("\n\n");//打印完某月后间隔换行打印下一个月的日历
	}

}

void test0() {
	printCalendar();
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

int calculateWeek(int year, int month, int day) {
	int index;
	char* week[] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wednesday" };
	int distance = calculateDistance(year, month, day);
	index = (distance % 7 + 7 - 3) % 7;//将以星期四为第一个元素的下标，转换成以星期日为第一个元素的下标
	return index;
}