#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "LinkList.h"
#include <limits.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* ���ÿ���ָ�뷨��ֱ�����������������
*  �������м����ֵ
*  �жϵ������Ƿ��л�
*/

ElemType findMidValueOfLinkList(LinkList* list) {
	//����Ϊ�գ�������Сֵ
	if (!list->head) {
		return INT_MIN;
	}
	LNode* fast_ptr = list->head;
	LNode* slow_ptr = list->head;
	while (fast_ptr->next) {
		//���fast_ptr->next->nextΪ�գ���ô���������ż�����ڵ㣬��ʱslow_ptr��ָ��Ľڵ㼴Ϊ�м�ֵ
		if (!fast_ptr->next->next) {
			return slow_ptr->data;
		}
		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;
	}
	//�����������ڵ㣬slow_ptr��ָ��Ľڵ�ֵΪ�м�ڵ�
	return slow_ptr->data;
}

bool hasCircleInLinkList(LinkList* list) {
	//����Ϊ�գ�������Сֵ
	if (!list->head) {
		return INT_MIN;
	}
	LNode* fast_ptr = list->head;
	LNode* slow_ptr = list->head;
	while (fast_ptr->next) {
		//���fast_ptr->next->nextΪ�գ���ô������β�ڵ㣬û�л�
		if (!fast_ptr->next->next) {
			return false;
		}
		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;
		if (fast_ptr == slow_ptr) {
			return true;
		}
	}
	return false;
}


void test0() {
	LinkList* list = create_linked_list();
	for (int i = 0; i < 10; ++i) {
		add_behind_tail(list, i * i);
	}
	printLinkLlist(list);
	printf("�����м��ֵΪ��%d\n", findMidValueOfLinkList(list));
	printf("�����Ƿ��л���%d\n", hasCircleInLinkList(list));

	printf("����β����� 999 ��\n");
	add_behind_tail(list, 999);
	printLinkLlist(list);
	printf("�����м��ֵΪ��%d\n",findMidValueOfLinkList(list));
	printf("�����Ƿ��л���%d\n", hasCircleInLinkList(list));

	printf("β��ָ��ڶ�������\n");
	list->tail->next = list->head->next->next;
	printf("�����Ƿ��л���%d\n", hasCircleInLinkList(list));
	list->tail->next = NULL;
	destroy_linked_list(list);
}

int main(void)
{
	test0();
	return 0;
}