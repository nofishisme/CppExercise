#include "HashMap.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

/* murmur_hash2 */
static uint32_t hash(const void* key, int len, uint32_t seed);

// 创建一个固定容量的哈希表
HashMap* create_hashmap() {
	HashMap* tmp = calloc(1, sizeof(HashMap));
	ERROR_INFO(tmp, NULL, "create_hashmap calloc error.\n");
	tmp->hash_sead = time(NULL);
	return tmp;
}
// 销毁一个哈希表
void destroy_hashmap(HashMap* map) {
	for (int i = 0; i < CAPACITY; ++i) {
		KeyValueNode* cur = map->buckets[i];
		while (cur) {
			KeyValueNode* tmp = cur->next;
			free(cur);
			cur = tmp;
		}
	}
	free(map);
}

// 插入一个键值对,重复Key返回旧值val，新Key返回NULL
Val put(HashMap* map, Key key, Val val) {
    //计算哈希值确定哈希桶的位置
	int idx = hash(key, strlen(key), map->hash_sead) % CAPACITY;
    //遍历哈希桶，查找Key值是否重复
    KeyValueNode* cur = map->buckets[idx];
    while (cur) {
        if (!strcmp(key, cur->key)) {
            Val old_val = cur->val;
            cur->val = val;
            return old_val;
        }
        cur = cur->next;
    }
    //Key值不重复，使用链表头插法插入节点
    KeyValueNode* new_node = malloc(sizeof(KeyValueNode));
    ERROR_INFO(new_node, NULL, "put new_node malloc error.\n");
    new_node->key = key;
    new_node->val = val;
    new_node->next = map->buckets[idx];
    map->buckets[idx] = new_node;
    //没有更新键值对返回空指针
    return NULL;
}
// 查询一个键值对，查询到返回对象val，未查询到返回NULL
Val get(HashMap* map, Key key) {
    //计算哈希值确定哈希桶的位置
    int idx = hash(key, strlen(key), map->hash_sead) % CAPACITY;
    //遍历哈希桶，查找Key值是否重复
    KeyValueNode* cur = map->buckets[idx];
    while (cur) {
        if (!strcmp(key, cur->key)) {
            return cur->val;
        }
        cur = cur->next;
    }
    return NULL;
}
// 删除某个键值对
bool map_remove(HashMap* map, Key key) {
    //计算哈希值确定哈希桶的位置
    int idx = hash(key, strlen(key), map->hash_sead) % CAPACITY;
    //遍历哈希桶，查找Key值是否重复
    KeyValueNode* cur = map->buckets[idx];
    KeyValueNode* pre = cur;
    //查找待删除节点
    while (cur) {
        if (!strcmp(key, cur->key)) {
            break;
        }
        pre = cur;
        cur = cur->next;
    }
    //没找到节点
    if (!cur) {
        return false;
    }
    //待删除节点是头结点
    if (cur == map->buckets[idx]) {
        map->buckets[idx] = map->buckets[idx]->next;
        free(cur);
        return true;
    }
    //带删除节点不是头结点
    pre->next = cur->next;
    free(cur);
    return true;
}

void printHashMap(HashMap* map) {
    for (int i = 0; i < CAPACITY; ++i) {
        printf("bucket[%d]:\n", i);
        KeyValueNode* cur = map->buckets[i];
        while (cur) {
            printf("      [key:%s]\n", cur->key);
            printf("      [val:%s]\n", cur->val);
            printf("      --------\n");
            cur = cur->next;
        }
    }
}

/* murmur_hash2 */
static uint32_t hash(const void* key, int len, uint32_t seed) {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t h = seed ^ len;
    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;
        k *= m;
        k ^= k >> r;
        k *= m;
        h *= m;
        h ^= k;
        data += 4;
        len -= 4;
    }

    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}