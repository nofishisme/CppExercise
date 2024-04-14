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

// ����������������

// ����һ���յ�����
LinkList* create_linked_list() {
	return calloc(1, sizeof(LinkList));
}

// ��������
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
// ͷ��������
bool add_before_head(LinkList* list, ElemType data) {
	LNode* tmp = malloc(sizeof(LNode));
	ERROR_INFO(tmp, NULL, "add_before_head malloc error\n");
	tmp->data = data;
	//���ԭ����Ϊ��
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
// β��������
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
// ������������
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
// ���������������
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
// ���������������
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

// ��������ɾ�����
bool delete_node_by_data(LinkList* list, ElemType data) {
	//�������ݲ��ҽڵ�
	LNode* tmp = search_by_data(list, data);
	
	//�ڵ㲻����
	if (!tmp) {
		return false;
	}
	
	//�ڵ����
	//��ֻ��һ���ڵ�
	if (list->size == 1) {
		free(tmp);
		list->head = NULL;
		list->tail = NULL;
		list->size == 0;
		return true;
	}
	//�ڵ����
	//�ж���ڵ㣬Ҫɾ��ͷ���
	if (tmp == list->head) {
		list->head = list->head->next;
		free(tmp);
		list->size--;
	}
	else {
		//�ж���ڵ㣬Ҫɾ���м���
		LNode* pre = list->head;
		while (pre->next && pre->next != tmp) {
			pre = pre->next;
		}
		pre->next = tmp->next;
		//���ɾ������β�ڵ㣬����Ҫ��β�ڵ��ָ��ֵ
		if (!pre->next) {
			list->tail = pre;
		}
		free(tmp);
		list->size--;
	}
	delete_node_by_data(list, data);//�ݹ�ɾ���ظ��ڵ�
	return true;
}

// ��������ɾ�����
bool delete_by_idx(LinkList* list, ElemType index) {
	if (index < 0 || index > list->size - 1) {
		return false;
	}
	LNode* tmp = list->head;
	//ֻ��һ���ڵ�
	if (list->size == 1) {
		list->head = NULL;
		list->tail = NULL;
		list->size--;
		return true;
	}
	//�ж�����ڵ�
	//ɾ��ͷ���
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
		//���ɾ������β�ڵ㣬����Ҫ��β�ڵ��ָ��ֵ
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

