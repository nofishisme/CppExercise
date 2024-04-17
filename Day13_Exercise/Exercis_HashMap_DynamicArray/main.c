#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "HashMapByDynamicArray.h"

#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

void test0() {
	HashMap* map = create_hashmap();
	char key[64];
	char val[64];
	put(map, "wuyu", "1111");
	put(map, "xiaomi", "2222");
	put(map, "huawei", "3333");
	put(map, "zijie", "4444");
	put(map, "meituan", "5555");
	put(map, "韩跑跑", "南宫婉");
	put(map, "苏铭", "雨萱");
	//printf("请输入五个键值对：key val（空格间隔）\n");
	/*for (int i = 0; i < 5; ++i) {
		printf("请输入第%d个键值对:", i + 1);
		scanf("%s %s", key, val);
		while (getchar() != '\n');
		printf("key: %s\n", key);
		printf("val: %s\n", val);
		put(map, key, val);
	}*/
	printHashMap(map);

	put(map, "叶凡", "姬紫月");
	put(map, "王林", "李慕婉");
	printHashMap(map);
	
}

int main(void)
{
	test0();
	return 0;
}