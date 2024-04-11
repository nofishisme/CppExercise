#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum Month
{
	Jan = 100,
	Feb = 101,
	Mar = 102,
	Apr = 103,
	May = 104,
	Jun = 105,
	Jul = 106,
	Aug = 107,
	Sep = 108,
	Oct = 109,
	Nov = 110,
	Dec = 111,
}Month;

int culculateMonthDays(Month mon) {
	int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	return mon - 100 >= 0 && mon - 100 < 12 ? days[mon - 100] : -1;
}

void test0() {
	Month month = Jan;
	printf("Jan ÌìÊýÊÇ£º%d\n", culculateMonthDays(month));
}

int main(void)
{
	test0();
	return 0;
}