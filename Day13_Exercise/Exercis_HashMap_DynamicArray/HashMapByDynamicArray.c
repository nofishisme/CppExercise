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
    //�ٹ�ϣ
    //�ȰѾ�Ͱ�������������ڽ���Ͱ���ݷ�����Ͱ
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
    //�ͷž�Ͱ����ļ�ֵ��
    for (int i = 0; i < old_capacity; ++i) {
        KeyValueNode* cur = old_buckets[i];
        while (cur) {
            KeyValueNode* tmp1 = cur->next;
            free(cur);
            cur = tmp1;
        }
    }
    //�ͷž�Ͱ
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

// ����һ���̶������Ĺ�ϣ��
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
// ����һ����ϣ��
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

// ����һ����ֵ�ԣ������ǰ��ϣ���װ�����Ӵ���Ԥ��ֵ����Ҫ���ж�̬�����ٹ�ϣ���ظ�Key���ؾ�ֵval����Key����NULL
V put(HashMap* map, K key, V val) {
	if ((double)map->size / map->capacity > loadfactor) {
		resize(map);
	}
    //�����ϣֵȷ����ϣͰ��λ��
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
    //������ϣͰ������Keyֵ�Ƿ��ظ�
    KeyValueNode* cur = map->buckets[idx];
    while (cur) {
        if (!strcmp(key, cur->key)) {
            V old_val = cur->val;
            cur->val = val;
            return old_val;
        }
        cur = cur->next;
    }
    //Keyֵ���ظ���ʹ������ͷ�巨����ڵ�
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
    //û�и��¼�ֵ�Է��ؿ�ָ��
    return NULL;
}
// ��ѯһ����ֵ�ԣ���ѯ�����ض���val��δ��ѯ������NULL
V get(HashMap* map, K key) {
    //�����ϣֵȷ����ϣͰ��λ��
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
    //������ϣͰ������Keyֵ�Ƿ��ظ�
    KeyValueNode* cur = map->buckets[idx];
    while (cur) {
        if (!strcmp(key, cur->key)) {
            return cur->val;
        }
        cur = cur->next;
    }
    return NULL;
}
// ɾ��ĳ����ֵ��
bool map_remove(HashMap* map, K key) {
    //�����ϣֵȷ����ϣͰ��λ��
    int idx = hash(key, strlen(key), map->hash_seed) % map->capacity;
    //������ϣͰ������Keyֵ�Ƿ��ظ�
    KeyValueNode* cur = map->buckets[idx];
    KeyValueNode* pre = cur;
    //���Ҵ�ɾ���ڵ�
    while (cur) {
        if (!strcmp(key, cur->key)) {
            break;
        }
        pre = cur;
        cur = cur->next;
    }
    //û�ҵ��ڵ�
    if (!cur) {
        return false;
    }
    //��ɾ���ڵ���ͷ���
    if (cur == map->buckets[idx]) {
        map->buckets[idx] = map->buckets[idx]->next;
    }//��ɾ���ڵ㲻��ͷ���
    else {
        pre->next = cur->next;
    }
    free(cur);
    map->size--;
    return true;
}