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
	//哈希桶
	KeyValueNode* buckets[CAPACITY];
	//哈希函数需要的种子值
	uint32_t hash_sead;
}HashMap;

// 创建一个固定容量的哈希表
HashMap* create_hashmap();
// 销毁一个哈希表
void destroy_hashmap(HashMap* map);

// 插入一个键值对
Val put(HashMap* map, Key key, Val val);
// 查询一个键值对
Val get(HashMap* map, Key key);
// 删除某个键值对
bool map_remove(HashMap* map, Key key);

void printHashMap(HashMap* map);

#endif // !HASHMAP_H
