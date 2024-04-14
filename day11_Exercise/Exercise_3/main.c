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

/* 利用快慢指针法，直接求解下列两个需求：
*  求链表中间结点的值
*  判断单链表是否有环
*/

ElemType findMidValueOfLinkList(LinkList* list) {
	//链表为空，返回最小值
	if (!list->head) {
		return INT_MIN;
	}
	LNode* fast_ptr = list->head;
	LNode* slow_ptr = list->head;
	while (fast_ptr->next) {
		//如果fast_ptr->next->next为空，那么链表就是有偶数个节点，此时slow_ptr所指向的节点即为中间值
		if (!fast_ptr->next->next) {
			return slow_ptr->data;
		}
		fast_ptr = fast_ptr->next->next;
		slow_ptr = slow_ptr->next;
	}
	//链表有奇数节点，slow_ptr所指向的节点值为中间节点
	return slow_ptr->data;
}

bool hasCircleInLinkList(LinkList* list) {
	//链表为空，返回最小值
	if (!list->head) {
		return INT_MIN;
	}
	LNode* fast_ptr = list->head;
	LNode* slow_ptr = list->head;
	while (fast_ptr->next) {
		//如果fast_ptr->next->next为空，那么链表有尾节点，没有环
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
	printf("链表中间的值为：%d\n", findMidValueOfLinkList(list));
	printf("链表是否有环：%d\n", hasCircleInLinkList(list));

	printf("链表尾部添加 999 后：\n");
	add_behind_tail(list, 999);
	printLinkLlist(list);
	printf("链表中间的值为：%d\n",findMidValueOfLinkList(list));
	printf("链表是否有环：%d\n", hasCircleInLinkList(list));

	printf("尾部指向第二个结点后：\n");
	list->tail->next = list->head->next->next;
	printf("链表是否有环：%d\n", hasCircleInLinkList(list));
	list->tail->next = NULL;
	destroy_linked_list(list);
}

int main(void)
{
	test0();
	return 0;
}