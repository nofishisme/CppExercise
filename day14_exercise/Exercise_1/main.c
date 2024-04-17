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

//删除链表连续的重复元素
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

//使用双节点指针判断，第一个指针head用于正序遍历链表，第二个指针tail用于逆序遍历链表，初始时都指向链表头结点
//先递归找到链表尾节点给到tail
//再将尾节点tail的值和头节点head的值进行对比，比较两个节点值是否相同
//  如果下一层递归结果是true且当层递归头尾节点的值相同，那么head继续遍历指向链表下一个节点，返回true，tail就继续指向链表逆序的下一个节点。
//  如果头尾节点的值不同，说明不是回文串，返回false；
//  为了让head节点指针在每一层递归时都能正确的修改，head必须是二级节点指针。
bool judegePalindromeRecrusion(LNode** head, LNode* tail) {
	bool ret = true;
	if (tail->next) {
		//让tail找到链表尾节点
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
	//这里使用递归方式，需要修改进行比较的头节点指针的值
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
	printf("是否是回文链表：");
	judegePalindrome(list->head) ? printf("是\n") : printf("否\n");
	add_behind_tail(list, 1);
	printLinkLlist(list);
	printf("是否是回文链表：");
	judegePalindrome(list->head) ? printf("是\n") : printf("否\n");
	/*printf("删除链表重复元素后：\n");
	deleteSuccessiveDuplicateElem(list->head);*/
	//printLinkLlist(list);
	
}

int main(void)
{
	test0();
	return 0;
}