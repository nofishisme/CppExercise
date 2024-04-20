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

/* 自己敲文件流的API实现以下功能：
* 
*  1.逐字符文本文件复制，函数声明是：
*  void copy_file_char(char* src_file, char* dest_file) {
* 
*  2.逐行文本文件复制，函数声明式：
*  void copy_file_line(char* src_file, char* dest_file) {
* 
*  3.用fread和fwrite函数实现二进制文件的复制, 函数声明如下：
*  void binary_file_cpy(char* src_file, char* dest_file) {
* 
*  4.用fread和fwrite函数实现二进制的序列化和反序列化。
*  此操作可以不提取函数，直接在main函数中实现即可。但只允许使用一个FILE流。
*/

typedef struct {
	char name[25];
	int age;
	char gender;
} Student;

//去除字符串中换行符
void processString(char* buff) {
	while (*buff && *buff++ != '\n') {
		buff++;
	}
	*buff = 0;
}

//1.逐字符文本文件复制，函数声明是：
void copy_file_char(char* src_file, char* dest_file) {
	FILE* ifs = fopen(src_file, "r");
	if (!ifs) {
		fprintf(stderr, "copy_file_char open src_file error.\n");
		exit(EXIT_FAILURE);
	}
	FILE* ofs = fopen(dest_file, "w");
	if (!ofs) {
		fprintf(stderr, "copy_file_char open dest_file error.\n");
		fclose(ifs);
		exit(EXIT_FAILURE);
	}
	char ch;
	while ((ch = fgetc(ifs)) != EOF){
		fputc(ch, ofs);
	}
	printf("源：%s----->目：%s复制完成\n", src_file, dest_file);
	fclose(ifs);
	fclose(ofs);
}
//2.逐行文本文件复制，函数声明式：
void copy_file_line(char* src_file, char* dest_file) {
	FILE* ifs = fopen(src_file, "r");
	if (!ifs) {
		fprintf(stderr, "copy_file_line open src_file error.\n");
		exit(EXIT_FAILURE);
	}
	FILE* ofs = fopen(dest_file, "w");
	if (!ofs) {
		fprintf(stderr, "copy_file_line open dest_file error.\n");
		fclose(ifs);
		exit(EXIT_FAILURE);
	}
	char buff[1024];
	while (fgets(buff, 1024, ifs)) {
		fputs(buff, ofs);
	}
	printf("源：%s----->目：%s复制完成\n", src_file, dest_file);
	fclose(ifs);
	fclose(ofs);
}
//3.用fread和fwrite函数实现二进制文件的复制, 函数声明如下：
void binary_file_cpy(char* src_file, char* dest_file) {
	FILE* ifs = fopen(src_file, "rb");
	if (!ifs) {
		fprintf(stderr, "binary_file_cpy open src_file error.\n");
		exit(EXIT_FAILURE);
	}
	FILE* ofs = fopen(dest_file, "wb");
	if (!ofs) {
		fprintf(stderr, "binary_file_cpy open dest_file error.\n");
		fclose(ifs);
		exit(EXIT_FAILURE);
	}
	
	int read_count;
	char buff[1024];
	while ((read_count = fread(buff, sizeof(char), 1024, ifs)) > 0) {
		fwrite(buff, sizeof(char), read_count, ofs);
	}

	// 写操作后及时刷新
	fflush(ofs);

	printf("源：%s----->目：%s复制完成\n", src_file, dest_file);
	fclose(ifs);
	fclose(ofs);
}
//4.用fread和fwrite函数实现二进制的序列化和反序列化。
void serialize(void) {
	Student s1 = { "hello", 18, 'm' };
	FILE* fs = fopen("1.dat", "wb");
	if (!fs) {
		fprintf(stderr, "serialize open file error.\n");
		exit(EXIT_FAILURE);
	}
	//序列化
	fwrite(&s1, sizeof(s1), 1, fs);
	fclose(fs);//序列化结束

	fs = fopen("1.dat", "rb");
	if (!fs) {
		fprintf(stderr, "serialize open file error.\n");
		exit(EXIT_FAILURE);
	}

	Student s2;
	fread(&s2, sizeof(s2), 1, fs);
	fclose(fs);

	// 打印读取的数据，以验证反序列化是否成功
	printf("s2:\n");
	printf("Name: %s\nAge: %d\nGender: %c\n", s2.name, s2.age, s2.gender);
	return 0;
	
}

void test0() {
	char src_file[] = "avatar.jpg";
	char dest_file[] = "仙逆副本.jpg";
	binary_file_cpy(src_file, dest_file);
	serialize();
}

int main(void)
{
	test0();
	return 0;
}