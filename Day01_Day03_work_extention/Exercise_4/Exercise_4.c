#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool judgeIsLeapYear(int year);//�ж��Ƿ�������
int calculateDistance(int year, int month, int day);//����ͻ�׼����1970/1/1����������
void getdate(char* date, int* year, int* month, int* day);//��������ַ���������ȡ��������

void calculateWeek() {
	char* week[] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wednesday" };
	char date[64];
	printf("������һ�����ڣ�xxxx/xxxx/xxxx����\n");
	scanf("%s", date);
	int year = 0, month = 0, day = 0;
	getdate(date, &year, &month, &day);
	int distance = calculateDistance(year, month, day);
	printf("%s �� %s", date, week[distance % 7]);
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
	//�������year�������
	for (int i = 1970; i < year; ++i) {
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
	distance--;//��Ϊ�������1970/1/1����һ��
	return distance;
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