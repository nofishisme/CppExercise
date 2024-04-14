#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 基于以下函数声明，实现函数：
*  void split_time(long total_sec, int* hour, int* minute, int* second);
*  形参中的 total_sec 表示从凌晨00:00:00开始，到现在时间的秒数。
*  请将 total_sec 转化以时(0-23)、分(0-59)、秒(0-59)表示的时间，
*  并存放到函数外部由指针 hour, minute, second 指向的变量中。
*  并在函数调用的位置，打印出当前的时间。
*/

#define HOUR_TO_SECOND 3600
#define MINUTES_TO_SECOND 60

void split_time(long total_sec, int* hour, int* minute, int* second) {
	*hour = total_sec / HOUR_TO_SECOND;
	*minute = total_sec % HOUR_TO_SECOND / MINUTES_TO_SECOND;
	*second = total_sec % HOUR_TO_SECOND % MINUTES_TO_SECOND;
	printf("当前时间是：%02d:%02d:%02d\n", *hour, *minute, *second);
}

void test0() {
	long total_sec;
	int hour, minute, second;
	total_sec = 0;
	split_time(total_sec, &hour, &minute, &second);
	total_sec = 9527;
	split_time(total_sec, &hour, &minute, &second);
	total_sec = 3001;
	split_time(total_sec, &hour, &minute, &second);
}

int main(void)
{
	test0();
	return 0;
}