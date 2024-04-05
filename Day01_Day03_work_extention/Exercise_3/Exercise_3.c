#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool judgeIsLeapYear(int year);//�ж��Ƿ�������
void getdate(char* date, int* year, int* month, int* day);//��������ַ���������ȡ��������
int calculateDistance(int year, int month, int day);//����ͻ�׼����1/1/1����������

void twoDateDistance(void) {
	char date1[64],date2[64];
	printf("�������һ�����ڣ�xxxx/xxxx/xxxx����\n");
	scanf("%s", date1);
	printf("������ڶ������ڣ�xxxx/xxxx/xxxx����\n");
	scanf("%s", date2);
	int year1 = 0, month1 = 0, day1 = 0;
	int year2 = 0, month2 = 0, day2 = 0;
	int distance;
	//��ȡyear1��month1��day1
	getdate(date1, &year1, &month1, &day1);
	//��ȡyear2��month2��day2
	getdate(date2, &year2, &month2, &day2);
	distance = calculateDistance(year2, month2, day2) - calculateDistance(year1, month1, day1);
	printf("%s �� %s ��� %d ��", date1, date2, distance);
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
	//��ȡyear��month��day
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
	//�������year�������
	for (int i = 1; i < year; ++i) {
		if (judgeIsLeapYear(i)) {
			distance += 366;
		}
		else {
			distance += 365;
		}
	}
	//�ۼ�year�꣬month��֮ǰ������
	//��������꣬2��������1
	if (judgeIsLeapYear(year)) {
		monthDays[1] = 29;
	}
	for (int j = 0; j < month - 1 && j < 11; ++j) {
		distance += monthDays[j];
	}
	//�ۼ�month�µ�����
	distance += day;
	return distance;
}