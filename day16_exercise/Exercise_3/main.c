#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* 用户输入文件名，将整个文件的内容读入到字符数组中，并在后面添加空字符'\0'。
*  
*  char* read_file(const char* path);
*  分析思路：
* 
*  1.打开文件，以只读模式打开即可。不要忘记进行打开失败，错误处理。
* 
*  2.此案例中文件的大小只能在运行时期确定，所以需要动态内存分配一个字符数组用于存储结果字符串。
* 
*  3.结果字符串的长度 = 文件字节大小 + 1
* 
*  4.文件字节大小怎么算？用ftell函数配合fseek函数即可计算。
* 
*  5.利用fread函数一次性将整个文件中的数据，全部读到结果字符数组中，然后自己在末尾加一个空字符。
*/

char* read_file(const char* path) {
	FILE* ifs = fopen(path, "r");
	if (!ifs) {
		fprintf(stderr, "read_file open file error.\n");
		exit(EXIT_FAILURE);
	}
	//找到文件末尾
	fseek(ifs, 0L, SEEK_END);
	//记录文件大小
	long file_count = ftell(ifs);
	//找到文件开头开始读取
	fseek(ifs, 0L, SEEK_SET);
	char* buff = calloc(file_count + 1, sizeof(char));
	if (!buff) {
		fprintf(stderr, "read_file calloc error.\n");
		fclose(ifs);
		exit(EXIT_FAILURE);
	}
	fread(buff, sizeof(char), file_count, ifs);
	fclose(ifs);
	return buff;
}

void test0() {
	printf("请输入文件路径：\n");
	char* dest = NULL;
	char* path[256];
	scanf("%s", path);
	dest = read_file(path);
	printf("%s", dest);
	if (dest) {
		free(dest);
	}
}

int main(void)
{
	test0();
	return 0;
}