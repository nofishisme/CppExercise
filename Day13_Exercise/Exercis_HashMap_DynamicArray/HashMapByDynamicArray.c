#define _CRT_SECURE_NO_WARNINGS
#include "HashMapByDynamicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int initialSize = 10;
static const int threshold = 1000;
static const double loadfactor = 0.75;

void printHashMap(HashMap* map) {
    for (int i = 0; i < map->capacity; ++i) {
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

static void resize(HashMap* map) {
    int old_capacity = map->capacity;
    int new_capacity = old_capacity < threshold ? old_capacity << 1 : old_capacity + (old_capacity >> 1);
    KeyValueNode** tmp = calloc(new_capacity, sizeof(KeyValueNode*));
    if (!tmp) {
        fprintf(stderr, "resize calloc error.\n");
        return;
    }
    //再哈希
    //先把旧桶保存下来，用于将旧桶数据放入新桶
    KeyValueNode** old_buckets = map->buckets;
    map->buckets = tmp;
    map->capacity = new_capacity;
    map->size = 0;
    for (int i = 0; i < old_capacity; ++i) {
        KeyValueNode* cur = old_buckets[i];
        while (cur) {
            put(map, cur->key, cur->val);
            cur = cur->next;
        }
    }
    //释放旧桶里面的键值对
    for (int i = 0; i < old_capacity; ++i) {
        KeyValueNode* cur = old_buckets[i];
        while (cur) {
            KeyValueNode* tmp1 = cur->next;
            free(cur);
            cur = tmp1;
        }
    }
    //释放旧桶
    free(old_buckets);
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

// 创建一个固定容量的哈希表
HashMap* create_hashmap() {
	HashMap* map = calloc(1, sizeof(HashMap));
	if (!map) {
		printf("create_hashmap calloc error.\n");
		exit(EXIT_FAILURE);
	}
    map->buckets = calloc(initialSize, sizeof(KeyValueNode*));
    if (!map->buckets) {
        printf("create_hashmap buckets calloc error.\n");
        free(map);
        exit(EXIT_FAILURE);
    }
	map->capacity = initialSize;
	map->hash_seed = time(NULL);
	return map;
}
// 销毁一个哈希表
void destroy_hashmap(HashMap* map) {
	for (int i = 0; i < map->capacity; ++i) {
		KeyValueNode* cur = map->buckets[i];
		while (cur) {
			KeyValueNode* tmp = cur->next;
			free(cur);
			cur = tmp;
		}
	}
    free(map->buckets);
	free(map);
}

// 插入一个键值对，如果当前哈希表的装载因子大于预设值，需要进行动态扩容再哈希，重复Key返回旧值val，新Key返回NULL
V put(HashMap* map, K key, V val) {
	if ((double)map->size / map->capacity > loadfactor) {
		resize(map);
	}
    //计算哈希值确定哈希桶的位置
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
    //遍历哈希桶，查找Key值是否重复
    KeyValueNode* cur = map->buckets[idx];
    while (cur) {
        if (!strcmp(key, cur->key)) {
            V old_val = cur->val;
            cur->val = val;
            return old_val;
        }
        cur = cur->next;
    }
    //Key值不重复，使用链表头插法插入节点
    KeyValueNode* new_node = malloc(sizeof(KeyValueNode));
    if (!new_node) {
        printf("put new_node malloc error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->val = val;
    new_node->next = map->buckets[idx];
    map->buckets[idx] = new_node;
    map->size++;
    //没有更新键值对返回空指针
    return NULL;
}
// 查询一个键值对，查询到返回对象val，未查询到返回NULL
V get(HashMap* map, K key) {
    //计算哈希值确定哈希桶的位置
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
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
bool map_remove(HashMap* map, K key) {
    //计算哈希值确定哈希桶的位置
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
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
    }//带删除节点不是头结点
    else {
        pre->next = cur->next;
    }
    free(cur);
    map->size--;
    return true;
}