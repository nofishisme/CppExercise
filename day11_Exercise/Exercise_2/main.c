#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "LinkList.h"

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* �ϲ���������ĵ�������ʹ�úϲ��������Ҳ������� (Ҫ��: ���ܶ���������ڴ�ռ�)��
*  ���룺
*  list1: 1 --> 3 --> 5
*  ist2: 2 --> 4 --> 6
*  �����
*  1 --> 2 --> 3 --> 4 --> 5 -->6
*  ������������ֱ��д:
*  Node* merge_two_lists(Node* list1, Node* list2);
*/

LNode* merge_two_lists(LNode * list1, LNode * list2) {
	//�ж������Ƿ�Ϊ��
	if (!list1 || !list2) {
		return !list1 ? list2 : list1;
	}
	//�����������е�һ���ڵ�ֵ��С�Ľڵ㵱�������ͷ���
	LNode* newList = list1->data < list2->data ? list1 : list2;
	LNode* cur1 = newList, * cur2 = newList == list1 ? list2 : list1;
	LNode* pre = cur1;
	while (cur1 && cur2) {
		if (cur1->data <= cur2->data) {
			pre = cur1;
			cur1 = cur1->next;
		}
		else {
			LNode* tmp = cur2;
			cur2 = cur2->next;
			//�ϲ�����
			tmp->next = cur1;
			pre->next = tmp;
			pre = tmp;
		}
	}
	if (!cur1) {
		pre->next = cur2;
		return newList;
	}
	return newList;
}


LNode* merge_two_lists_recursion(LNode* list1, LNode* list2) {
	//�ж������Ƿ�Ϊ��
	if (!list1 || !list2) {
		return !list1 ? list2 : list1;
	}

	if (list1->data < list2->data) {
		list1->next =  merge_two_lists_recursion(list1->next, list2);
	}
	else {
		list2->next = merge_two_lists_recursion(list1, list2->next);
	}

	return list1->data < list2->data ? list1 : list2;
}

void printList(LNode* list) {
	while (list) {
		printf("%d ", list->data);
		list = list->next;
	}
	printf("\n");
}

void test0() {
	LinkList* list1 = create_linked_list();
	LinkList* list2 = create_linked_list();
	for (int i = 0; i < 5; ++i) {
		add_behind_tail(list1, i * i);
	}
	printf("list1 ��ֵ�ǣ�\n");
	printLinkLlist(list1);
	for (int i = 0; i < 5; ++i) {
		add_behind_tail(list2, i * i * i);
	}
	printf("list2 ��ֵ�ǣ�\n");
	printLinkLlist(list2);

	printf("list1 ��list2 �ϲ����ֵ�ǣ�\n");
	LNode* list3 = merge_two_lists_recursion(list1->head, list2->head);
	printList(list3);
}

int main(void)
{
	test0();
	return 0;
}