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


// 基础操作

//创建一棵二叉搜索树
BST* bst_create() {
	BST* bst = calloc(1, sizeof(BST));
	ERROR_INFO(bst, NULL, "bst_create calloc error.\n");
	return bst;
}


//销毁一棵树
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

//二叉搜索树中插入一个元素
bool bst_insert(BST* tree, ElemType key) {
	TreeNode* insert_node = calloc(1, sizeof(TreeNode));
	if (!insert_node) {
		printf("bst_insert calloc error.\n");
		return false;
	}
	insert_node->data = key;
	//如果二叉树原来就为空
	if (!tree->root) {
		tree->root = insert_node;
	}
	else {
		//二叉树原来不为空
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
//查找节点
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
	//先查找值节点和它的父节点
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
	//1.不存在该节点
	if (!cur) {
		printf("节点删除失败，无该节点");
		return false;
	}
	//2.待删除节点为根节点且该节点度小于2
	if (cur == tree->root && (!cur->left || !cur->right)) {
		tree->root = cur->left ? cur->left : cur->right;
		free(cur);
		tree->size--;
		return true;
	}
	//3.待删除节点不是根节点，该节点度小于2
	if (!cur->left || !cur->right) {
		//找到该节点的左子树或者右子树
		TreeNode* tmp = cur->left ? cur->left : cur->right;
		pre->data > key ? (pre->left = tmp) : (pre->right = tmp);
		free(cur);
	}//4.待删除节点不是根节点，该节点度等于2，找到待删除节点前驱节点替换
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

// 先序遍历
void bst_preorder(BST* tree) {
	//树为空
	if (!tree->root) {
		return;
	}
	//创建一个栈来遍历二叉排序树
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
// 中序遍历
void bst_inorder(BST* tree) {
	//树为空
	if (!tree->root) {
		return;
	}
	//创建一个栈来遍历二叉排序树
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
// 后序遍历
void bst_postorder(BST* tree) {
	//树为空
	if (!tree->root) {
		return;
	}
	//创建一个栈来遍历二叉排序树
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
//层序遍历
void bst_levelorder(BST* tree) {
	//创建一个队列来遍历二叉排序树
	TreeNode** queue = malloc(tree->size * sizeof(TreeNode*));
	if (!queue) {
		printf("bst_levelorder malloc error.\n");
		return;
	}
	TreeNode* cur = NULL;
	int front = -1, rear = -1;
	queue[++rear] = tree->root;
	while (front != rear){
		//队头元素出队
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