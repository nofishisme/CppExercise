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


typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode;

//���·����ö���ָ��ʵ��
// ͷ�巨����һ�����
void insert_head(LNode * *list, ElemType val);
// �޸ĵ�һ������Ԫ��ֵ���������Ϊ�գ�����new_val��ʼ����һ�����
void modify_first_LNode(LNode * *list, int new_val);
// β�巨����һ�����
void insert_tail(LNode * *list, ElemType val);
//��ӡ����
void printLinkList(const LNode* list);
//�ͷ�����
void destroyLinkList(LNode** lsit);

void test0() {
	LNode* list = NULL;
	for (int i = 0; i < 10; ++i) {
		insert_tail(&list, i * i);
	}
	printLinkList(list);

	printf("����β����� 999 ��\n");
	insert_tail(&list, 999);
	printLinkList(list);

	printf("����ͷ����� 999 ��\n");
	insert_head(&list, 999);
	printLinkList(list);

	printf("�޸�����ͷ��Ϊ777��\n");
	modify_first_LNode(&list, 777);
	printLinkList(list);

	destroyLinkList(&list);
}

int main(void)
{
	test0();
	return 0;
}

// ͷ�巨����һ�����
void insert_head(LNode** list, ElemType val) {
	LNode* tmp = calloc(1, sizeof(LNode));
	ERROR_INFO(tmp, NULL, "insert_head calloc error.\n");
	tmp->data = val;
	//����Ϊ��
	if (!(*list)) {
		*list = tmp;
		return;
	}
	//������
	tmp->next = *list;
	(*list) = tmp;
	return;

}
// �޸ĵ�һ������Ԫ��ֵ���������Ϊ�գ�����new_val��ʼ����һ�����
void modify_first_LNode(LNode** list, int new_val) {
	//�������Ϊ��
	if (!(*list)) {
		*list = calloc(1, sizeof(LNode));
		ERROR_INFO(*list, NULL, "modify_first_LNode calloc error.\n");
		(*list)->data = new_val;
		return;
	}
	(*list)->data = new_val;
}
// β�巨����һ�����
void insert_tail(LNode** list, ElemType val) {
	LNode* tmp = calloc(1, sizeof(LNode));
	ERROR_INFO(tmp, NULL, "insert_head calloc error.\n");
	tmp->data = val;
	//����Ϊ��
	if (!(*list)) {
		*list = tmp;
		return;
	}
	//������
	LNode* cur = *list;
	while (cur && cur->next) {
		cur = cur->next;
	}
	cur->next = tmp;
}

void printLinkList(const LNode* list) {
	while (list) {
		printf("%d ", list->data);
		list = list->next;
	}
	printf("\n");
}

void destroyLinkList(LNode** list) {
	while (*list) {
		LNode* tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}