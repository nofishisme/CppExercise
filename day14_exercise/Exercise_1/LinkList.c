#define _CRT_SECURE_NO_WARNINGS
#include "Linklist.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					return false;\
				 } \
			} while(0)

// 基础操作函数声明

// 创建一个空的链表
LinkList* create_linked_list() {
	return calloc(1, sizeof(LinkList));
}

// 销毁链表
void destroy_linked_list(LinkList* list) {
	if (!list) {
		return;
	}
	while (list->head) {
		LNode* tmp = list->head->next;
		free(list->head);
		list->head = tmp;
	}
	free(list);
}
// 头部插入结点
bool add_before_head(LinkList* list, ElemType data) {
	LNode* tmp = malloc(sizeof(LNode));
	ERROR_INFO(tmp, NULL, "add_before_head malloc error\n");
	tmp->data = data;
	//如果原链表为空
	if (!list->head) {
		list->head = tmp;
		list->tail = tmp;
		list->size++;
		return true;
	}
	tmp->next = list->head;
	list->head = tmp;
	list->size++;
	return true;
}
// 尾部插入结点
bool add_behind_tail(LinkList* list, ElemType data) {
	LNode* tmp = calloc(1, sizeof(LNode));
	ERROR_INFO(tmp, NULL, "add_behind_tail calloc error\n");
	tmp->data = data;
	if (!list->head) {
		list->head = tmp;
		list->tail = tmp;
		list->size++;
		return true;
	}
	list->tail->next = tmp;
	list->tail = tmp;
	list->size++;
	return true;
}
// 按索引插入结点
bool add_index(LinkList* list, int index, ElemType data) {
	if (index < 0 || index > list->size - 1) {
		return false;
	}
	if (index == 0) {
		return add_before_head(list, data);
	}
	else if (index == list->size - 1) {
		return add_behind_tail(list, data);
	}
	LNode* cur = list->head;
	while (index > 1) {
		cur = cur->next;
		index--;
	}
	LNode* tmp = malloc(sizeof(LNode));
	ERROR_INFO(tmp, NULL, "add_index calloc error\n");
	tmp->data = data;
	tmp->next = cur->next;
	cur->next = tmp;
	list->size++;
	return true;
}
// 根据索引搜索结点
LNode* search_by_index(LinkList* list, int index) {
	if (index < 0 || index > list->size - 1) {
		return NULL;
	}
	LNode* cur = list->head;
	while (index) {
		cur = cur->next;
		index--;
	}
	return cur;
}
// 根据数据搜索结点
LNode* search_by_data(LinkList* list, ElemType data) {
	LNode* cur = list->head;
	while (cur){
		if (cur->data == data) {
			return cur;
		}
		cur = cur->next;
	}
	return false;
}

// 根据数据删除结点
bool delete_node_by_data(LinkList* list, ElemType data) {
	//根据数据查找节点
	LNode* tmp = search_by_data(list, data);
	
	//节点不存在
	if (!tmp) {
		return false;
	}
	
	//节点存在
	//且只有一个节点
	if (list->size == 1) {
		free(tmp);
		list->head = NULL;
		list->tail = NULL;
		list->size == 0;
		return true;
	}
	//节点存在
	//有多个节点，要删除头结点
	if (tmp == list->head) {
		list->head = list->head->next;
		free(tmp);
		list->size--;
	}
	else {
		//有多个节点，要删除中间结点
		LNode* pre = list->head;
		while (pre->next && pre->next != tmp) {
			pre = pre->next;
		}
		pre->next = tmp->next;
		//如果删除的是尾节点，还需要改尾节点的指针值
		if (!pre->next) {
			list->tail = pre;
		}
		free(tmp);
		list->size--;
	}
	delete_node_by_data(list, data);//递归删除重复节点
	return true;
}

// 根据索引删除结点
bool delete_by_idx(LinkList* list, ElemType index) {
	if (index < 0 || index > list->size - 1) {
		return false;
	}
	LNode* tmp = list->head;
	//只有一个节点
	if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return true;
	}
	//有多个个节点
	//删除头结点
	if (index == 0) {
		list->head = list->head->next;
		free(tmp);
		list->size--;
	}
	else {
		LNode* pre = list->head;
		while (index > 1) {
			pre = pre->next;
			index--;
		}
		tmp = pre->next;
		pre->next = tmp->next;
		//如果删除的是尾节点，还需要改尾节点的指针值
		if (!pre->next) {
			list->tail = pre;
		}
		free(tmp);
		list->size--;
	}
	return true;
}

void printLinkLlist(const LinkList* list) {
	LNode* tmp = list->head;
	while (tmp) {
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

