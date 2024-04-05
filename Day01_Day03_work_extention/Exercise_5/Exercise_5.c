#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdbool.h>
#include <ctype.h>

bool judgeIsLeapYear(int year);//�ж��Ƿ�������
int calculateDistance(int year, int month, int day);//����ͻ�׼����1970/1/1����������
int calculateWeek(int year, int month, int day);//���ص�ǰ���ڵ���weeks�е��±꣬��ʾ�����ڵ����ڼ�,weeks�����д�������������ڵ����ڣ�����������Ϊ��һ��Ԫ�ء�

void printCalendar(void) {
	int year;
	char* weeks[] = { "SUN","MON","TUE","WED","THU","FRI","SAT" };
	char* months[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
	int monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	printf("������һ����ݣ�\n");
	scanf("%d", &year);
	if (judgeIsLeapYear(year)) {//����2�¶�һ��
		monthDays[1] = 29;
	}
	printf("=====================The Calendar of Year %d=====================\n", year);
	int dayToWeek = calculateWeek(year, 1, 1);//�����һ���Ӧ����weeks�е��±꣬ʹ�ø��±������weeks�в鵽���������ڼ���
	for (int i = 0; i < 12; ++i) {
		printf("%s\n", months[i]);//��ӡ�·�
		printf("%s %s %s %s %s %s %s\n", weeks[0], weeks[1], weeks[2], weeks[3], weeks[4], weeks[5], weeks[6]);//��ӡ����
		for (int j = 0; j < monthDays[i]; ++j,dayToWeek = (dayToWeek + 1) % 7) {//�����������ģ�����Ҳ�������ģ�����dayToWeekֻ��Ҫÿ�μ�1Ȼ���7ȡģ��������һ�����ڵ������±ꡣ
			if (j == 0) {//�������Ǹ��µ�һ�죬�������µ�һҳ�����������ڶ���ǰ����Ҫ����
				for (int k = 0; k < dayToWeek; ++k) {//��ȷ����һ�������ڼ�����ÿһ������׿ո�����趨3���ټ���һ������õĿհ׷�һ���ĸ��հ׷���Ҫ������һ����һ��֮���λ�����ס�
					printf("    ");
				}
			}
			printf("%3d", j + 1);//��ӡ���ڣ�3��ռλ��
			if (dayToWeek == 6) {
				printf("\n");//�����������,��Ҫ����
			}
			else {
				printf(" ");//�����������������Ҫ�ӿո��ַ����м��
			}
		}
		printf("\n\n");//��ӡ��ĳ�º������д�ӡ��һ���µ�����
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

int calculateWeek(int year, int month, int day) {
	int index;
	char* week[] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wednesday" };
	int distance = calculateDistance(year, month, day);
	index = (distance % 7 + 7 - 3) % 7;//����������Ϊ��һ��Ԫ�ص��±꣬ת������������Ϊ��һ��Ԫ�ص��±�
	return index;
}