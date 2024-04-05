#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void scoreToGrade() {
	int score;
	char grade;
	printf("please input a score:\n");
	scanf("%d", &score);
	switch (score / 10)
	{
	case 9:
	case 10:
		grade = 'A';
		break;
	case 8:
		grade = 'B';
		break;
	case 7:
		grade = 'C';
		break;
	case 6:
		grade = 'D';
		break;
	case 5:
	case 4:
	case 3:
	case 2:
	case 1:
	case 0:
		grade = 'F';
		break;
	default:
		printf("Error,please input a valid score!!!!");
		return;
	}
	printf("Your Grade is: %c", grade);
}

void test0() {
	scoreToGrade();
}

int main(void)
{
	test0();
	return 0;
}