#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

typedef struct Date {
	int year;
	int month;
	int day;
}Date;

int calculateDistanceOfTwoDays(Date date1, Date date2) {
	return abs(date1.year - date2.year) * 360 +
		abs(date1.month - date2.month) * 30 +
		abs(date1.day - date2.day);
}

void test0() {
	Date date1 = { 2021,1,2 };
	Date date2 = { 2023,3,4 };
	printf("date1 : %d/%d/%d\n", date1.year, date1.month, date1.day);
	printf("date2 : %d/%d/%d\n", date2.year, date2.month, date2.day);
	printf("两天的间隔:%d\n", calculateDistanceOfTwoDays(date1, date2));
}

int main(void)
{
	test0();
	return 0;
}