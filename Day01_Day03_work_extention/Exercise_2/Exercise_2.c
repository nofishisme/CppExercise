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
	printf("������һ�����ڣ�xxxx/xxxx/xxxx����\n");
	scanf("%s", date);
	int year = 0, month = 0, day = 0;
	int flag = 0;
	//��ȡyear��month��day
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
	//�ж�ƽ������Ȼ��д��ÿ������
	int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (judgeIsLeapYear(year)) {
		monthDays[1] = 29;
	}
	//������һ��
	day++;
	if (month > 0 && day > monthDays[month - 1]) {
		day = day - monthDays[month - 1];
		month++;
		if (month > 12) {
			month = month - 12;
			year++;
		}
	}
	printf("%d��%d��%d��\n", year, month, day);
}

void test0() {
	theNextDay();
}

int main(void)
{
	test0();
	return 0;
}