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

/* �û������ļ������������ļ������ݶ��뵽�ַ������У����ں�����ӿ��ַ�'\0'��
*  
*  char* read_file(const char* path);
*  ����˼·��
* 
*  1.���ļ�����ֻ��ģʽ�򿪼��ɡ���Ҫ���ǽ��д�ʧ�ܣ�������
* 
*  2.�˰������ļ��Ĵ�Сֻ��������ʱ��ȷ����������Ҫ��̬�ڴ����һ���ַ��������ڴ洢����ַ�����
* 
*  3.����ַ����ĳ��� = �ļ��ֽڴ�С + 1
* 
*  4.�ļ��ֽڴ�С��ô�㣿��ftell�������fseek�������ɼ��㡣
* 
*  5.����fread����һ���Խ������ļ��е����ݣ�ȫ����������ַ������У�Ȼ���Լ���ĩβ��һ�����ַ���
*/

char* read_file(const char* path) {
	FILE* ifs = fopen(path, "r");
	if (!ifs) {
		fprintf(stderr, "read_file open file error.\n");
		exit(EXIT_FAILURE);
	}
	//�ҵ��ļ�ĩβ
	fseek(ifs, 0L, SEEK_END);
	//��¼�ļ���С
	long file_count = ftell(ifs);
	//�ҵ��ļ���ͷ��ʼ��ȡ
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
	printf("�������ļ�·����\n");
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