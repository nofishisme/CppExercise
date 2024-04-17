#define _CRT_SECURE_NO_WARNINGS
#include "Linklist.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

//ɾ�������������ظ�Ԫ��
LNode* deleteSuccessiveDuplicateElem(LNode * list) {
	LNode* pre = list, * cur = list->next;
	if (!pre || !cur) {
		return list;
	}
	while (cur) {
		if (pre->data == cur->data) {
			pre->next = cur->next;
			free(cur);
			cur = pre->next;
		}
		else {
			pre = cur;
			cur = cur->next;
		}
	}
	return list;
}

//ʹ��˫�ڵ�ָ���жϣ���һ��ָ��head����������������ڶ���ָ��tail�����������������ʼʱ��ָ������ͷ���
//�ȵݹ��ҵ�����β�ڵ����tail
//�ٽ�β�ڵ�tail��ֵ��ͷ�ڵ�head��ֵ���жԱȣ��Ƚ������ڵ�ֵ�Ƿ���ͬ
//  �����һ��ݹ�����true�ҵ���ݹ�ͷβ�ڵ��ֵ��ͬ����ôhead��������ָ��������һ���ڵ㣬����true��tail�ͼ���ָ�������������һ���ڵ㡣
//  ���ͷβ�ڵ��ֵ��ͬ��˵�����ǻ��Ĵ�������false��
//  Ϊ����head�ڵ�ָ����ÿһ��ݹ�ʱ������ȷ���޸ģ�head�����Ƕ����ڵ�ָ�롣
bool judegePalindromeRecrusion(LNode** head, LNode* tail) {
	bool ret = true;
	if (tail->next) {
		//��tail�ҵ�����β�ڵ�
		ret = judegePalindromeRecrusion(head, tail->next);
	}
	if (ret && (*head)->data == tail->data) {
		(*head) = (*head)->next;
		return true;
	}
	else {
		return false;
	}
}

bool judegePalindrome(LNode* list) {
	if (!list || !list->next) {
		return true;
	}
	LNode* head = list, * tail = list;
	//����ʹ�õݹ鷽ʽ����Ҫ�޸Ľ��бȽϵ�ͷ�ڵ�ָ���ֵ
	return judegePalindromeRecrusion(&head, tail);
}

void test0() {
	int a;
	LinkList* list = create_linked_list();
	add_behind_tail(list, 1);
	add_behind_tail(list, 2);
	add_behind_tail(list, 3);
	add_behind_tail(list, 2);
	add_behind_tail(list, 1);
	/*add_behind_tail(list, 4);
	add_behind_tail(list, 4);
	add_behind_tail(list, 4);
	add_behind_tail(list, 5);*/
	printLinkLlist(list);
	printf("�Ƿ��ǻ�������");
	judegePalindrome(list->head) ? printf("��\n") : printf("��\n");
	add_behind_tail(list, 1);
	printLinkLlist(list);
	printf("�Ƿ��ǻ�������");
	judegePalindrome(list->head) ? printf("��\n") : printf("��\n");
	/*printf("ɾ�������ظ�Ԫ�غ�\n");
	deleteSuccessiveDuplicateElem(list->head);*/
	//printLinkLlist(list);
	
}

int main(void)
{
	test0();
	return 0;
}