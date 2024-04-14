#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "LinkList.h"
#include <limits.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/*  ����һ���������뷴ת����������
*  ������
*  ����: 1 --> 2 --> 3
*  ���: 3 --> 2 --> 1
*  �������º���������ʵ�֣�
*  Node* reverse(Node *list); // ��ת��ǰ�����������µ�ͷָ��
*  ע�⣺
*  ����õݹ��ѭ���������ַ�ʽ���������⡣
*/

//�ǵݹ��ͷ�巨��ת����
LNode* reverse1(LNode* list) {
	//ֻ��һ��ͷ���
	if (!list->next) {
		return list;
	}
	LNode* tmp_head = calloc(1, sizeof(LNode));
	ERROR_INFO(tmp_head, NULL, "reverse1 calloc error\n");
	tmp_head->next = list;
	LNode* pre = list, * cur = list->next;
	while (cur){
		pre ->next = cur->next;
		cur->next = tmp_head->next;
		tmp_head->next = cur;
		cur = pre->next;
	}
	cur = tmp_head->next;
	free(tmp_head);
	return cur;

}

//����õݹ鷭ת����
LNode* reverse2(LNode* list) {
	if (list == NULL || list->next == NULL) {
		return list;
	}
	LNode* ret = reverse2(list->next);
	list->next->next = list; 
	list->next = NULL;
	return ret;
}



void test0() {
	LinkList* list = create_linked_list();
	for (int i = 0; i < 10; ++i) {
		add_behind_tail(list, i * i);
	}
	printLinkLlist(list);
	printf("��������ת��\n");
	list->tail = list->head;
	list->head = reverse1(list->head);//������ת����
	printLinkLlist(list);
	printf("�ݹ�����ת��\n");
	list->tail = list->head;
	list->head = reverse2(list->head);//������ת����
	printLinkLlist(list);
	destroy_linked_list(list);
}

int main(void)
{
	test0();
	return 0;
}