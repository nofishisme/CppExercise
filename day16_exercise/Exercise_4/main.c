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

/* ��дһ��C����ʵ�����¹��ܣ�
*  1.�����Դ�һ����Ϊ "1.txt" ���ļ����ж�������
* 
*  2.����ļ��ɹ��򿪣��������ȡ�ļ��ĵ�һ�����ݣ�������������ն��ϡ�
* 
*  3.����ļ���ʧ�ܣ�����Ӧʹ�� perror ������ӡ�ļ����Լ�������Ϣ������� errno ��ǰ��ֵ��
* 
*  ִ�����²�����
* 
*  1.һ��ʼ��1.txt�ļ������ڣ��۲����������
* 
*  2.�ڹ���Ŀ¼�´���1.txt�ļ��������ļ���ͷ�ֶ�д��һ���ַ������ٹ۲����������
* 
*  3.��1.txt�ļ���Ȩ�޸ĳ�ֻ��ģʽ��Ȼ�󽫴�ģʽ�ĳ�׷��ģʽ������׷��д��һ���ַ������۲����������
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
	printf("�ļ���һ��������:\n%s", buff);
	fclose(ifs);

	//�ļ�ֻ��������׷�Ӳ���
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