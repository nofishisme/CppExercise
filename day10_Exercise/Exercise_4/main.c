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

//以下方法用二级指针实现
// 头插法新增一个结点
void insert_head(LNode * *list, ElemType val);
// 修改第一个结点的元素值，如果链表为空，则用new_val初始化第一个结点
void modify_first_LNode(LNode * *list, int new_val);
// 尾插法新增一个结点
void insert_tail(LNode * *list, ElemType val);
//打印链表
void printLinkList(const LNode* list);
//释放链表
void destroyLinkList(LNode** lsit);

void test0() {
	LNode* list = NULL;
	for (int i = 0; i < 10; ++i) {
		insert_tail(&list, i * i);
	}
	printLinkList(list);

	printf("链表尾部添加 999 后：\n");
	insert_tail(&list, 999);
	printLinkList(list);

	printf("链表头部添加 999 后：\n");
	insert_head(&list, 999);
	printLinkList(list);

	printf("修改链表头部为777后：\n");
	modify_first_LNode(&list, 777);
	printLinkList(list);

	destroyLinkList(&list);
}

int main(void)
{
	test0();
	return 0;
}

// 头插法新增一个结点
void insert_head(LNode** list, ElemType val) {
	LNode* tmp = calloc(1, sizeof(LNode));
	ERROR_INFO(tmp, NULL, "insert_head calloc error.\n");
	tmp->data = val;
	//链表为空
	if (!(*list)) {
		*list = tmp;
		return;
	}
	//链表不空
	tmp->next = *list;
	(*list) = tmp;
	return;

}
// 修改第一个结点的元素值，如果链表为空，则用new_val初始化第一个结点
void modify_first_LNode(LNode** list, int new_val) {
	//如果链表为空
	if (!(*list)) {
		*list = calloc(1, sizeof(LNode));
		ERROR_INFO(*list, NULL, "modify_first_LNode calloc error.\n");
		(*list)->data = new_val;
		return;
	}
	(*list)->data = new_val;
}
// 尾插法新增一个结点
void insert_tail(LNode** list, ElemType val) {
	LNode* tmp = calloc(1, sizeof(LNode));
	ERROR_INFO(tmp, NULL, "insert_head calloc error.\n");
	tmp->data = val;
	//链表为空
	if (!(*list)) {
		*list = tmp;
		return;
	}
	//链表不空
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