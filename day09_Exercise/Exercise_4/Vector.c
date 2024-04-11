#define _CRT_SECURE_NO_WARNINGS
#include "Vector.h"

static const int initialSize = 10;
static const int threshold = 1000;

static void resize(Vector* v);

Vector* vector_create() {
	Vector* vec = calloc(1, sizeof(Vector));
	if (!vec) {
		fprintf(stderr, "malloc of Vector error!\n");
		return NULL;
	}
	vec->capacity = initialSize;
	vec->data = calloc(initialSize, sizeof(ElemType));
	if (!vec->data) {
		fprintf(stderr, "malloc of Vector->data error!\n");
		free(vec);
		return NULL;
	}
	return vec;
}

void vector_destroy(Vector* v) {
	free(v->data);
	free(v);
}

void vector_push_back(Vector* v, ElemType element) {
	if (v->size == v->capacity) {
		resize(v);
	}
	*(v->data + v->size++) = element;
}

//在动态数组最前面添加元素，所有元素依次后移
void vector_push_front(Vector* v, ElemType val) {
	if (v->size == v->capacity) {
		resize(v);
	}
	for (int i = v->size; i > 0; --i) {
		v->data[i] = v->data[i - 1];
	}
	*v->data = val;
	v->size++;
}

//将元素val添加到索引为idx的位置，idx后面的元素依次后移
void vector_insert(Vector* v, int idx, ElemType val) {
	//如果标号小于0，直接在数组开头插入
	if (idx > v->size - 1) {
		vector_push_front(v, val);
		return;
	}
	//如果标号大于现有动态数组内的元素数目，直接在末尾插入
	if (idx > v->size - 1) {
		vector_push_back(v, val);
		return;
	}
	if (v->size == v->capacity) {
		resize(v);
	}
	for (int i = v->size; i > idx; --i) {
		v->data[i] = v->data[i - 1];
	}
	v->data[idx] = val;
	v->size++;
}

int vector_size(Vector* v) {
	return v->size;
}

int vector_capacity(Vector* v) {
	return v->capacity;
}

static void resize(Vector* v) {
	int old_capacity = v->capacity;
	int new_capacity = old_capacity < threshold ? old_capacity << 1 : old_capacity + (old_capacity >> 1);
	ElemType* tmp = realloc(v->data, new_capacity * sizeof(ElemType));
	if (!tmp) {
		fprintf(stderr, "Vector realloc error.\n");
		return;
	}
	v->data = tmp;
	v->capacity = new_capacity;
}