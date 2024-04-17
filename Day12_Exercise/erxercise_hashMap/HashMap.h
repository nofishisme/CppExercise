#pragma once
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>
#include <stdbool.h>

#define CAPACITY 10

typedef char* Key;
typedef char* Val;

typedef struct PNode {
	Key key;
	Val val;
	struct PNode* next;
}KeyValueNode;

typedef struct {
	//��ϣͰ
	KeyValueNode* buckets[CAPACITY];
	//��ϣ������Ҫ������ֵ
	uint32_t hash_sead;
}HashMap;

// ����һ���̶������Ĺ�ϣ��
HashMap* create_hashmap();
// ����һ����ϣ��
void destroy_hashmap(HashMap* map);

// ����һ����ֵ��
Val put(HashMap* map, Key key, Val val);
// ��ѯһ����ֵ��
Val get(HashMap* map, Key key);
// ɾ��ĳ����ֵ��
bool map_remove(HashMap* map, Key key);

void printHashMap(HashMap* map);

#endif // !HASHMAP_H
