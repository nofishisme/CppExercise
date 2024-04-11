#define _CRT_SECURE_NO_WARNINGS
#include "Vector.h"

/* vector��ʵ��
*  ��ʼ��һ��Vector��̬����.��ʵ������ģ����C++��Ĭ�Ϲ��캯��
*  Vector* vector_create();
*
*  ����һ��Vector��̬���飬�ͷ��ڴ档��ʵ����ģ����C++����������
*  void vector_destroy(Vector *v);
*
*  ��̬����ĩβ���һ��Ԫ��
*  void vector_push_back(Vector *v, ElementType element);
*
*  �ڶ�̬������ǰ�����Ԫ�أ�����Ԫ�����κ���
*  void vector_push_front(Vector* v, E val);
*
*  ��Ԫ��val��ӵ�����Ϊidx��λ�ã�idx�����Ԫ�����κ���
*  void vector_insert(Vector* v, int idx, E val);
*/

char* my_strcat(const char* prefix, const char* suffix) {
	char* tmp = malloc(strlen(prefix) + strlen(suffix) + 1);
	char* start = tmp;
	if (!start) {
		fprintf(stderr, "my_strcat malloc error\n");
		return NULL;
	}
	while (*prefix && (*tmp++ = *prefix++));
	while (*suffix && (*tmp++ = *suffix++));
	*tmp = 0;
	return start;
}

void test0() {
	Vector *vec = vector_create();
	printf("vec ��ʼ��������: %d\n", vector_capacity(vec));
	//char buff[2] = {0};
	char insert_ch[1024] = { 0 };
	//ʹ���Զ����my_srtcat��������һ��ƴ�Ӻ���µ��ַ���ָ�룬Ȼ��push��vec��
	for (int i = 0; i < 100; ++i) {
		char str[5];
		snprintf(str, sizeof(str), "%d", i % 10);
		char* ch = my_strcat(insert_ch, str);
		strcpy(insert_ch, ch);
		vector_push_back(vec, ch);
		//_itoa(i % 10, buff, 10);
		//if (i == 0) {//��ʼ����һ���ַ���
		//	vector_push_back(vec, my_strcat(buff, ""));
		//	continue;
		//}
		//vector_push_back(vec, my_strcat(vec->data[i - 1], buff));
	}

	for (int i = 0; i < 100; i++) {
		printf("%s\n", vec->data[i]);
	}

	while (vec->size > 0) {
		free(vec->data[--vec->size]);
	}
	vector_destroy(vec);
}

int main(void)
{
	test0();
	return 0;
}

/*switch (i % 10)
{
case 0:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "0"));
	break;
case 1:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "1"));
	break;
case 2:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "2"));
	break;
case 3:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "3"));
	break;
case 4:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "4"));
	break;
case 5:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "5"));
	break;
case 6:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "6"));
	break;
case 7:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "7"));
	break;
case 8:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "8"));
	break;
case 9:
	vector_push_back(vec, my_strcat(vec->data[i - 1], "9"));
	break;
default:
	break;
}*/