#pragma once
#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <stdbool.h>
#include <stdint.h>

typedef char* K;
typedef char* V;

typedef struct node_s {
	K key;
	V val;
	struct node_s* next;
} KeyValueNode;

typedef struct {
	KeyValueNode** buckets;   // ��ʱ��ϣͰ��һ����̬����
	int size;       // ��ֵ�Եĸ���
	int capacity;   // ����ĳ���
	uint32_t hash_seed;  // ��ϣ������Ҫ������ֵ
} HashMap;

// �����Ĳ�������Ա���һ��

// ����һ���̶������Ĺ�ϣ��
HashMap* create_hashmap();
// ����һ����ϣ��
void destroy_hashmap(HashMap* map);

// ����һ����ֵ��
V put(HashMap* map, K key, V val);
// ��ѯһ����ֵ��
V get(HashMap* map, K key);
// ɾ��ĳ����ֵ��
bool map_remove(HashMap* map, K key);

#endif // !HASH_MAP_H