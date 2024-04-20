#define _CRT_SECURE_NO_WARNINGS
#include "HashMapByDynamicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100 // 初始容量是8，设置为10足以触发一次扩容

int main() {
	// 创建哈希表
	HashMap *map = create_hashmap();
	if (map == NULL) {
		printf("哈希表创建失败。\n");
		return 1;
	}

	// 插入多个键值对以触发扩容
	char tmp_key[1024], tmp_val[1024];
	for (int i = 0; i < N; i++) {
		/*
			sprintf是一个将格式化的数据输出到一个字符数组中，并最终保存为字符串的标准库函数
			第一个参数是输出的目的地字符串
			后面的参数则和printf使用方式一样
		*/
		sprintf(tmp_key, "key%d", i);
		sprintf(tmp_val, "value%d", i);

		// 使用 calloc 分配和复制键值对
		char *key = calloc(strlen(tmp_key) + 1, sizeof(char));
		char *val = calloc(strlen(tmp_val) + 1, sizeof(char));
		if (!key || !val) {
			printf("内存分配失败.\n");
			exit(1);
		}
		strcpy(key, tmp_key);
		strcpy(val, tmp_val);

		put(map, key, val);
		printf("插入 %s: %s\n", key, val);
	}

	// 检查扩容前后的数据一致性
	bool flag = true;
	for (int i = 0; i < N; i++) {
		sprintf(tmp_key, "key%d", i);
		V ret_val = get(map, tmp_key);
		sprintf(tmp_val, "value%d", i);
		if (ret_val == NULL || strcmp(ret_val, tmp_val) != 0) {
			printf("错误：数据不一致，键 %s 应有的值为 %s，检索得到的值为 %s\n",
				tmp_key, tmp_val,
				((ret_val != NULL) ? ret_val : "null"));
			flag = false;	// 若数据插入有问题，则修改标志为false
		}
	}

	if (flag) {
		printf("所有数据在扩容后仍正确无误。\n");
	}

	// free所有堆上分配的字符串
	for (int i = 0; i < map->capacity; i++) {
		KeyValueNode *curr = map->buckets[i];
		while (curr != NULL) {
			free(curr->key);   // 释放键字符串
			free(curr->val);   // 释放值字符串
			curr = curr->next; // 移动到下一个节点
		}
	}

	// 销毁哈希表
	destroy_hashmap(map);
	return 0;
}
