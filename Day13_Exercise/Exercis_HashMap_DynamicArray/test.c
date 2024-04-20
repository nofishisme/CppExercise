#define _CRT_SECURE_NO_WARNINGS
#include "HashMapByDynamicArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100 // ��ʼ������8������Ϊ10���Դ���һ������

int main() {
	// ������ϣ��
	HashMap *map = create_hashmap();
	if (map == NULL) {
		printf("��ϣ����ʧ�ܡ�\n");
		return 1;
	}

	// ��������ֵ���Դ�������
	char tmp_key[1024], tmp_val[1024];
	for (int i = 0; i < N; i++) {
		/*
			sprintf��һ������ʽ�������������һ���ַ������У������ձ���Ϊ�ַ����ı�׼�⺯��
			��һ�������������Ŀ�ĵ��ַ���
			����Ĳ������printfʹ�÷�ʽһ��
		*/
		sprintf(tmp_key, "key%d", i);
		sprintf(tmp_val, "value%d", i);

		// ʹ�� calloc ����͸��Ƽ�ֵ��
		char *key = calloc(strlen(tmp_key) + 1, sizeof(char));
		char *val = calloc(strlen(tmp_val) + 1, sizeof(char));
		if (!key || !val) {
			printf("�ڴ����ʧ��.\n");
			exit(1);
		}
		strcpy(key, tmp_key);
		strcpy(val, tmp_val);

		put(map, key, val);
		printf("���� %s: %s\n", key, val);
	}

	// �������ǰ�������һ����
	bool flag = true;
	for (int i = 0; i < N; i++) {
		sprintf(tmp_key, "key%d", i);
		V ret_val = get(map, tmp_key);
		sprintf(tmp_val, "value%d", i);
		if (ret_val == NULL || strcmp(ret_val, tmp_val) != 0) {
			printf("�������ݲ�һ�£��� %s Ӧ�е�ֵΪ %s�������õ���ֵΪ %s\n",
				tmp_key, tmp_val,
				((ret_val != NULL) ? ret_val : "null"));
			flag = false;	// �����ݲ��������⣬���޸ı�־Ϊfalse
		}
	}

	if (flag) {
		printf("�������������ݺ�����ȷ����\n");
	}

	// free���ж��Ϸ�����ַ���
	for (int i = 0; i < map->capacity; i++) {
		KeyValueNode *curr = map->buckets[i];
		while (curr != NULL) {
			free(curr->key);   // �ͷż��ַ���
			free(curr->val);   // �ͷ�ֵ�ַ���
			curr = curr->next; // �ƶ�����һ���ڵ�
		}
	}

	// ���ٹ�ϣ��
	destroy_hashmap(map);
	return 0;
}
