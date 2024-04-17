#define _CRT_SECURE_NO_WARNINGS
#include "BST.h"
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

void test0() {
	BST* bst = bst_create();
	bst_insert(bst, 30);
	bst_insert(bst, 40);
	bst_insert(bst, 10);
	bst_insert(bst, 15);
	bst_insert(bst, 5);
	bst_insert(bst, 3);
	bst_insert(bst, 12);
	bst_insert(bst, 35);
	bst_insert(bst, 70);
	bst_insert(bst, 75);

	printf("先序遍历结果是：\n");
	bst_preorder(bst);

	printf("中序遍历结果是：\n");
	bst_inorder(bst);

	printf("后序遍历结果是：\n");
	bst_postorder(bst);

	printf("层序遍历结果是：\n");
	bst_levelorder(bst);

	/*bst_delete(bst,75);
	bst_delete(bst, 70);
	bst_delete(bst, 35);
	bst_delete(bst, 40);*/
	
	printf("删除30后：\n");
	bst_delete(bst, 30);

	printf("先序遍历结果是：\n");
	bst_preorder(bst);

	printf("中序遍历结果是：\n");
	bst_inorder(bst);

	printf("后序遍历结果是：\n");
	bst_postorder(bst);

	printf("层序遍历结果是：\n");
	bst_levelorder(bst);

	bst_destroy(bst);
}

int main(void)
{
	test0();
	return 0;
}