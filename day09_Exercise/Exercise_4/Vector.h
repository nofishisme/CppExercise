#pragma once
#ifndef __VECTOR_H
#define __VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* vector��ʵ��
*  ��ʼ��һ��Vector��̬����.��ʵ������ģ����C++��Ĭ�Ϲ��캯��
*  Vector* vector_create();
*
*  ����һ��Vector��̬���飬�ͷ��ڴ档��ʵ����ģ����C++����������
*  void vector_destroy(Vector *v);
*
*  ��̬����ĩβ���һ��Ԫ��
*  void vector_push_back(Vector *v, ElemType element);
* 
*  �ڶ�̬������ǰ�����Ԫ�أ�����Ԫ�����κ���
*  void vector_push_front(Vector* v, ElemType val);
* 
*  ��Ԫ��val��ӵ�����Ϊidx��λ�ã�idx�����Ԫ�����κ���
*  void vector_insert(Vector* v, int idx, ElemType val);
*/

typedef char* ElemType;

typedef struct {
	ElemType* data;//ָ��̬���������ָ��
	int size;//��ǰ��̬����Ԫ�ص�����
	int capacity;//��̬���鵱ǰ������������
}Vector;

Vector* vector_create();

void vector_destroy(Vector* v);

void vector_push_back(Vector* v, ElemType element);

void vector_push_front(Vector* v, ElemType val);

void vector_insert(Vector* v, int idx, ElemType val);

int vector_size(Vector* v);

int vector_capacity(Vector* v);

#endif // !__VECTOR_H
