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
	KeyValueNode** buckets;   // 此时哈希桶是一个动态数组
	int size;       // 键值对的个数
	int capacity;   // 数组的长度
	uint32_t hash_seed;  // 哈希函数需要的种子值
} HashMap;

// 基础的操作则可以保持一致

// 创建一个固定容量的哈希表
HashMap* create_hashmap();
// 销毁一个哈希表
void destroy_hashmap(HashMap* map);

// 插入一个键值对
V put(HashMap* map, K key, V val);
// 查询一个键值对
V get(HashMap* map, K key);
// 删除某个键值对
bool map_remove(HashMap* map, K key);

#endif // !HASH_MAP_H