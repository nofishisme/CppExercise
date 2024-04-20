#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* 编写一个C程序，实现以下功能：
*  1.程序尝试打开一个名为 "1.txt" 的文件进行读操作。
* 
*  2.如果文件成功打开，程序则读取文件的第一行内容，并将其输出到终端上。
* 
*  3.如果文件打开失败，程序应使用 perror 函数打印文件名以及错误信息，并输出 errno 当前的值。
* 
*  执行以下操作：
* 
*  1.一开始，1.txt文件不存在，观察程序的输出。
* 
*  2.在工作目录下创建1.txt文件，并在文件开头手动写入一行字符串，再观察程序的输出。
* 
*  3.将1.txt文件的权限改成只读模式，然后将打开模式改成追加模式，尝试追加写入一行字符串，观察程序的输出。
*/

void test0() {
	FILE* ifs = fopen("1.txt", "r");
	if (!ifs) {
		perror("file 1.txt open error.\n");
		printf("errno: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	char buff[1024];
	fgets(buff, 1024, ifs);
	printf("文件第一行内容是:\n%s", buff);
	fclose(ifs);

	//文件只读但进行追加操作
	FILE* ofs = fopen("1.txt", "a+");
	if (!ofs) {
		perror("file 1.txt open error.\n");
		printf("errno: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	char buff2[1024] = "I love you so much!!!!!!";
	fputs(buff2, ofs);
	fclose(ofs);

}

int main(void)
{
	test0();
	return 0;
}