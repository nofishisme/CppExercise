#pragma once
#ifndef BST_H
#define BST_H

#include<stdbool.h>

typedef int ElemType;

typedef struct node {
	ElemType data;
	struct node* left;  // ������
	struct node* right; // ������
} TreeNode;

// �Ƽ�����һ�������������Ľṹ��,������������չ
typedef struct {
	TreeNode* root; // �����
	int size;
}BST;

// ��������
BST* bst_create();
void bst_destroy(BST* tree);

bool bst_insert(BST* tree, ElemType key);
TreeNode* bst_search(BST* tree, ElemType key);
bool bst_delete(BST* tree, ElemType key);

void bst_preorder(BST* tree); // �������
void bst_inorder(BST* tree);  // �������
void bst_postorder(BST* tree);  // �������
void bst_levelorder(BST* tree); // ��α���

#endif // !BST_H