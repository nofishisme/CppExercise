#define _CRT_SECURE_NO_WARNINGS
#include "BST.h"
#include <stdlib.h>
#include <stdio.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)


// ��������

//����һ�ö���������
BST* bst_create() {
	BST* bst = calloc(1, sizeof(BST));
	ERROR_INFO(bst, NULL, "bst_create calloc error.\n");
	return bst;
}


//����һ����
static void bst_post_destroy(TreeNode* root) {
	if (!root) {
		return;
	}
	bst_post_destroy(root->left);
	bst_post_destroy(root->right);
	free(root);
}

void bst_destroy(BST* tree) {
	bst_post_destroy(tree->root);
	free(tree);
}

//�����������в���һ��Ԫ��
bool bst_insert(BST* tree, ElemType key) {
	TreeNode* insert_node = calloc(1, sizeof(TreeNode));
	if (!insert_node) {
		printf("bst_insert calloc error.\n");
		return false;
	}
	insert_node->data = key;
	//���������ԭ����Ϊ��
	if (!tree->root) {
		tree->root = insert_node;
	}
	else {
		//������ԭ����Ϊ��
		TreeNode* cur = tree->root, * pre = cur;
		while (cur) {
			if (key > cur->data) {
				pre = cur;
				cur = cur->right;
			}
			else {
				pre = cur;
				cur = cur->left;
			}
		}
		pre->data > key ? (pre->left = insert_node) : (pre->right = insert_node);
	}
	tree->size++;
	return true;
}
//���ҽڵ�
TreeNode* bst_search(BST* tree, ElemType key) {
	TreeNode* curr = tree->root;
	while (curr) {
		if (curr->data == key) {
			return curr;
		}
		else if (curr->data > key) {
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}
	return false;
}
bool bst_delete(BST* tree, ElemType key) {
	//�Ȳ���ֵ�ڵ�����ĸ��ڵ�
	TreeNode* cur = tree->root, * pre = cur;
	while (cur && cur->data != key) {
		if (key > cur->data) {
			pre = cur;
			cur = cur->right;
		}
		else {
			pre = cur;
			cur = cur->left;
		}
	}
	//1.�����ڸýڵ�
	if (!cur) {
		printf("�ڵ�ɾ��ʧ�ܣ��޸ýڵ�");
		return false;
	}
	//2.��ɾ���ڵ�Ϊ���ڵ��Ҹýڵ��С��2
	if (cur == tree->root && (!cur->left || !cur->right)) {
		tree->root = cur->left ? cur->left : cur->right;
		free(cur);
		tree->size--;
		return true;
	}
	//3.��ɾ���ڵ㲻�Ǹ��ڵ㣬�ýڵ��С��2
	if (!cur->left || !cur->right) {
		//�ҵ��ýڵ������������������
		TreeNode* tmp = cur->left ? cur->left : cur->right;
		pre->data > key ? (pre->left = tmp) : (pre->right = tmp);
		free(cur);
	}//4.��ɾ���ڵ㲻�Ǹ��ڵ㣬�ýڵ�ȵ���2���ҵ���ɾ���ڵ�ǰ���ڵ��滻
	else {
		TreeNode* new_cur = cur->left;
		pre = new_cur;
		while (new_cur->right) {
			pre = new_cur;
			new_cur = new_cur->right;
		}
		cur->data = new_cur->data;
		TreeNode* tmp = new_cur->left ? new_cur->left : new_cur->right;
		pre->data > key ? (pre->left = tmp) : (pre->right = tmp);
		free(new_cur);
	}
	tree->size--;
	return true;
}

// �������
void bst_preorder(BST* tree) {
	//��Ϊ��
	if (!tree->root) {
		return;
	}
	//����һ��ջ����������������
	TreeNode** stack = malloc(tree->size * sizeof(TreeNode*));
	if (!stack) {
		printf("bst_preorder malloc error.\n");
		return;
	}
	int top = -1;
	TreeNode* cur = tree->root;
	while (cur || top != -1) {
		if (cur) {
			printf("%d ", cur->data);
			stack[++top] = cur;
			cur = cur->left;
		}
		else {
			cur = stack[top--];
			cur = cur->right;
		}
	}
	printf("\n");
	free(stack);
}
// �������
void bst_inorder(BST* tree) {
	//��Ϊ��
	if (!tree->root) {
		return;
	}
	//����һ��ջ����������������
	TreeNode** stack = malloc(tree->size * sizeof(TreeNode*));
	if (!stack) {
		printf("bst_inorder malloc error.\n");
		return;
	}
	int top = -1;
	TreeNode* cur = tree->root;
	while (cur || top != -1) {
		if (cur) {
			stack[++top] = cur;
			cur = cur->left;
		}
		else {
			cur = stack[top--];
			printf("%d ", cur->data);
			cur = cur->right;
		}
	}
	printf("\n");
	free(stack);
}
// �������
void bst_postorder(BST* tree) {
	//��Ϊ��
	if (!tree->root) {
		return;
	}
	//����һ��ջ����������������
	TreeNode** stack = malloc(tree->size * sizeof(TreeNode*));
	if (!stack) {
		printf("bst_postorder malloc error.\n");
		return;
	}
	int top = -1;
	TreeNode* cur = tree->root, *pre = cur;
	while (cur || top != -1) {
		if (cur) {
			stack[++top] = cur;
			cur = cur->left;
		}
		else {
			cur = stack[top];
			if (cur->right && cur->right != pre) {
				cur = cur->right;
			}
			else {
				cur = stack[top--];
				printf("%d ", cur->data);
				pre = cur;
				cur = NULL;
			}
		}
	}
	printf("\n");
	free(stack);
}
//�������
void bst_levelorder(BST* tree) {
	//����һ����������������������
	TreeNode** queue = malloc(tree->size * sizeof(TreeNode*));
	if (!queue) {
		printf("bst_levelorder malloc error.\n");
		return;
	}
	TreeNode* cur = NULL;
	int front = -1, rear = -1;
	queue[++rear] = tree->root;
	while (front != rear){
		//��ͷԪ�س���
		cur = queue[++front];
		printf("%d ", cur->data);
		if (cur->left) {
			queue[++rear] = cur->left;
		}
		if (cur->right) {
			queue[++rear] = cur->right;
		}
	}
	printf("\n");
	free(queue);
}