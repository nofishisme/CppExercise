#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \{ if(rvalue == error_sign){printf(msg, __VA_ARGS__);exit(1);}}

void test0() {
	char* tmp = NULL;
	ERROR_INFO(tmp, NULL, "error,tmp is NULL %s", "ÎÒ°®Äã");
}

int main(void)
{
	test0();
	return 0;
}