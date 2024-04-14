#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Linklist.h"
#include <limits.h>

/* 定义一个链表Linklist
*  基础操作函数声明
*  LinkList* create_linked_list();                     // 创建一个空的链表
*  void destroy_linked_list(LinkList* list);           // 销毁链表
*  bool add_before_head(LinkList* list, ElemType data);        // 头部插入结点
*  bool add_behind_tail(LinkList* list, ElemType data);        // 尾部插入结点
*  bool add_index(LinkList* list, int index, ElemType data); // 按索引插入结点
*  LNode* search_by_index(LinkList* list, int index);          // 根据索引搜索结点
*  LNode* search_by_data(LinkList* list, ElemType data);             // 根据数据搜索结点
*  bool delete_node_by_data(LinkList* list, ElemType data);         // 根据数据删除结点
*  打印链表
*  void printLinkLlist(const LinkList* list);
*/

//错误报告宏定义
#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)



void test0() {
	int a;
	LinkList* list = create_linked_list();
	for (int i = 0; i < 10; ++i) {
		add_behind_tail(list, i * i);
	}
	printLinkLlist(list);

	printf("链表尾部添加 999 后：\n");
	add_behind_tail(list, 999);
	printLinkLlist(list);

	printf("链表头部添加 999 后：\n");
	add_before_head(list, 999);
	printLinkLlist(list);

	printf("链表索引5的地方添加 999 后：\n");
	add_index(list, 5, 999);
	printLinkLlist(list);

	printf("删除链表元素 999 后：\n");
	delete_node_by_data(list, 999);
	printLinkLlist(list);

	printf("链表尾部添加 64 后：\n");
	add_behind_tail(list, 64);
	printLinkLlist(list);

	printf("删除下标索引为 8 的元素之后：\n");
	delete_by_idx(list, 8);
	printLinkLlist(list);

	printf("链表中索引为 8 的元素的值是：%d\n", search_by_index(list,8)->data);
	
	printf("链表中元素的值为 64 的是：%d\n", search_by_data(list,64) ? search_by_data(list, 64)->data : INT_MIN);

	destroy_linked_list(list);
}
 
int main(void)
{
	test0();
	return 0;
}