#pragma once
#ifndef __VECTOR_H
#define __VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* vector的实现
*  初始化一个Vector动态数组.这实际上是模拟了C++的默认构造函数
*  Vector* vector_create();
*
*  销毁一个Vector动态数组，释放内存。这实际上模拟了C++的析构函数
*  void vector_destroy(Vector *v);
*
*  向动态数组末尾添加一个元素
*  void vector_push_back(Vector *v, ElemType element);
* 
*  在动态数组最前面添加元素，所有元素依次后移
*  void vector_push_front(Vector* v, ElemType val);
* 
*  将元素val添加到索引为idx的位置，idx后面的元素依次后移
*  void vector_insert(Vector* v, int idx, ElemType val);
*/

typedef char* ElemType;

typedef struct {
	ElemType* data;//指向动态分配数组的指针
	int size;//当前动态数组元素的数量
	int capacity;//动态数组当前分配的最大容量
}Vector;

Vector* vector_create();

void vector_destroy(Vector* v);

void vector_push_back(Vector* v, ElemType element);

void vector_push_front(Vector* v, ElemType val);

void vector_insert(Vector* v, int idx, ElemType val);

int vector_size(Vector* v);

int vector_capacity(Vector* v);

#endif // !__VECTOR_H
