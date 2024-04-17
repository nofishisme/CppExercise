#pragma once
#ifndef BST_H
#define BST_H

#include<stdbool.h>

typedef int ElemType;

typedef struct node {
	ElemType data;
	struct node* left;  // 左子树
	struct node* right; // 右子树
} TreeNode;

// 推荐定义一个二叉搜索树的结构体,这样更便于扩展
typedef struct {
	TreeNode* root; // 根结点
	int size;
}BST;

// 基础操作
BST* bst_create();
void bst_destroy(BST* tree);

bool bst_insert(BST* tree, ElemType key);
TreeNode* bst_search(BST* tree, ElemType key);
bool bst_delete(BST* tree, ElemType key);

void bst_preorder(BST* tree); // 先序遍历
void bst_inorder(BST* tree);  // 中序遍历
void bst_postorder(BST* tree);  // 后序遍历
void bst_levelorder(BST* tree); // 层次遍历

#endif // !BST_H