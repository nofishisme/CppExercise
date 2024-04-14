#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "Linklist.h"
#include <limits.h>

/* ����һ������Linklist
*  ����������������
*  LinkList* create_linked_list();                     // ����һ���յ�����
*  void destroy_linked_list(LinkList* list);           // ��������
*  bool add_before_head(LinkList* list, ElemType data);        // ͷ��������
*  bool add_behind_tail(LinkList* list, ElemType data);        // β��������
*  bool add_index(LinkList* list, int index, ElemType data); // ������������
*  LNode* search_by_index(LinkList* list, int index);          // ���������������
*  LNode* search_by_data(LinkList* list, ElemType data);             // ���������������
*  bool delete_node_by_data(LinkList* list, ElemType data);         // ��������ɾ�����
*  ��ӡ����
*  void printLinkLlist(const LinkList* list);
*/

//���󱨸�궨��
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

	printf("����β����� 999 ��\n");
	add_behind_tail(list, 999);
	printLinkLlist(list);

	printf("����ͷ����� 999 ��\n");
	add_before_head(list, 999);
	printLinkLlist(list);

	printf("��������5�ĵط���� 999 ��\n");
	add_index(list, 5, 999);
	printLinkLlist(list);

	printf("ɾ������Ԫ�� 999 ��\n");
	delete_node_by_data(list, 999);
	printLinkLlist(list);

	printf("����β����� 64 ��\n");
	add_behind_tail(list, 64);
	printLinkLlist(list);

	printf("ɾ���±�����Ϊ 8 ��Ԫ��֮��\n");
	delete_by_idx(list, 8);
	printLinkLlist(list);

	printf("����������Ϊ 8 ��Ԫ�ص�ֵ�ǣ�%d\n", search_by_index(list,8)->data);
	
	printf("������Ԫ�ص�ֵΪ 64 ���ǣ�%d\n", search_by_data(list,64) ? search_by_data(list, 64)->data : INT_MIN);

	destroy_linked_list(list);
}
 
int main(void)
{
	test0();
	return 0;
}