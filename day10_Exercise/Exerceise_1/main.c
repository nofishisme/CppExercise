#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* �������º���������ʵ�ֺ�����
*  void split_time(long total_sec, int* hour, int* minute, int* second);
*  �β��е� total_sec ��ʾ���賿00:00:00��ʼ��������ʱ���������
*  �뽫 total_sec ת����ʱ(0-23)����(0-59)����(0-59)��ʾ��ʱ�䣬
*  ����ŵ������ⲿ��ָ�� hour, minute, second ָ��ı����С�
*  ���ں������õ�λ�ã���ӡ����ǰ��ʱ�䡣
*/

#define HOUR_TO_SECOND 3600
#define MINUTES_TO_SECOND 60

void split_time(long total_sec, int* hour, int* minute, int* second) {
	*hour = total_sec / HOUR_TO_SECOND;
	*minute = total_sec % HOUR_TO_SECOND / MINUTES_TO_SECOND;
	*second = total_sec % HOUR_TO_SECOND % MINUTES_TO_SECOND;
	printf("��ǰʱ���ǣ�%02d:%02d:%02d\n", *hour, *minute, *second);
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