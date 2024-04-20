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

/* �Լ����ļ�����APIʵ�����¹��ܣ�
* 
*  1.���ַ��ı��ļ����ƣ����������ǣ�
*  void copy_file_char(char* src_file, char* dest_file) {
* 
*  2.�����ı��ļ����ƣ���������ʽ��
*  void copy_file_line(char* src_file, char* dest_file) {
* 
*  3.��fread��fwrite����ʵ�ֶ������ļ��ĸ���, �����������£�
*  void binary_file_cpy(char* src_file, char* dest_file) {
* 
*  4.��fread��fwrite����ʵ�ֶ����Ƶ����л��ͷ����л���
*  �˲������Բ���ȡ������ֱ����main������ʵ�ּ��ɡ���ֻ����ʹ��һ��FILE����
*/

typedef struct {
	char name[25];
	int age;
	char gender;
} Student;

//ȥ���ַ����л��з�
void processString(char* buff) {
	while (*buff && *buff++ != '\n') {
		buff++;
	}
	*buff = 0;
}

//1.���ַ��ı��ļ����ƣ����������ǣ�
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
	printf("Դ��%s----->Ŀ��%s�������\n", src_file, dest_file);
	fclose(ifs);
	fclose(ofs);
}
//2.�����ı��ļ����ƣ���������ʽ��
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
	printf("Դ��%s----->Ŀ��%s�������\n", src_file, dest_file);
	fclose(ifs);
	fclose(ofs);
}
//3.��fread��fwrite����ʵ�ֶ������ļ��ĸ���, �����������£�
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

	// д������ʱˢ��
	fflush(ofs);

	printf("Դ��%s----->Ŀ��%s�������\n", src_file, dest_file);
	fclose(ifs);
	fclose(ofs);
}
//4.��fread��fwrite����ʵ�ֶ����Ƶ����л��ͷ����л���
void serialize(void) {
	Student s1 = { "hello", 18, 'm' };
	FILE* fs = fopen("1.dat", "wb");
	if (!fs) {
		fprintf(stderr, "serialize open file error.\n");
		exit(EXIT_FAILURE);
	}
	//���л�
	fwrite(&s1, sizeof(s1), 1, fs);
	fclose(fs);//���л�����

	fs = fopen("1.dat", "rb");
	if (!fs) {
		fprintf(stderr, "serialize open file error.\n");
		exit(EXIT_FAILURE);
	}

	Student s2;
	fread(&s2, sizeof(s2), 1, fs);
	fclose(fs);

	// ��ӡ��ȡ�����ݣ�����֤�����л��Ƿ�ɹ�
	printf("s2:\n");
	printf("Name: %s\nAge: %d\nGender: %c\n", s2.name, s2.age, s2.gender);
	return 0;
	
}

void test0() {
	char src_file[] = "avatar.jpg";
	char dest_file[] = "���渱��.jpg";
	binary_file_cpy(src_file, dest_file);
	serialize();
}

int main(void)
{
	test0();
	return 0;
}