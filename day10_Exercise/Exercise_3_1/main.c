#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

/* 你的任务是使用qsort函数对这个结构体数组进行排序：
*  先按照每个坐标点到原点(0, 0)的距离从小到大进行排序。
*  如果两个坐标点距离相同，则先按x值的大小从小到大排序,。
*  如果x的值一致, 再按照y值从大到小进行排序。
*/


#define ERROR_INFO(rvalue, error_sign, msg, ...) \
			do {\
				 if ((rvalue) == (error_sign)){ \
					printf(msg, __VA_ARGS__); \
					exit(1);\
				 } \
			} while(0)

typedef struct {
	int x;
	int y;
} Point;

int comparePoint(const Point* p1, const Point* p2) {
	double distance_p1 = p1->x * p1->x + p1->y * p1->y;
	double distance_p2 = p2->x * p2->x + p2->y * p2->y;
	if (distance_p1 != distance_p2) {
		return distance_p1 < distance_p2 ? -1 : 1;
	}
	if (p1->x != p2->x) {
		return p1->x < p2->x ? -1 : 1;
	}
	if (p1->y != p2->y) {
		return p1->y > p2->y ? -1 : 1;
	}
	return 0;
}

void printPoints(const Point* points) {
	for (int i = 0; i < 16; ++i) {
		printf("X: %d",points[i].x);
		printf("  Y: %d\n",points[i].y);
	}
}

void test0() {
	Point points[] = { {3, 3},{-2, -2},{-1, -2},{0, 0},{2, 2},{-2, 2},{3, 4},{2, -2},{6, 3},{-4, 4},{4, 4},{10, 2},{-4, -4},{0, 4},{-4, 0},{4, 0}, };
	printf("对points数组使用qsort函数之前：\n");
	printPoints(points);
	printf("对points数组使用qsort函数之后：\n");
	qsort(points, 16, sizeof(Point), comparePoint);
	printPoints(points);
}

int main(void)
{
	test0();
	return 0;
}