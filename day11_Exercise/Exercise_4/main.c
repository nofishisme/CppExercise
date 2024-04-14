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

/*  给定一条单链表，请反转这条单链表。
*  举例，
*  输入: 1 --> 2 --> 3
*  输出: 3 --> 2 --> 1
*  基于以下函数的声明实现：
*  Node* reverse(Node *list); // 反转当前单链表并返回新的头指针
*  注意：
*  请采用递归和循环迭代两种方式求解这个问题。
*/

//非递归的头插法翻转链表。
LNode* reverse1(LNode* list) {
	//只有一个头结点
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

//请采用递归翻转链表。
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
	printf("迭代链表翻转后：\n");
	list->tail = list->head;
	list->head = reverse1(list->head);//遍历翻转链表
	printLinkLlist(list);
	printf("递归链表翻转后：\n");
	list->tail = list->head;
	list->head = reverse2(list->head);//遍历翻转链表
	printLinkLlist(list);
	destroy_linked_list(list);
}

int main(void)
{
	test0();
	return 0;
}