#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/* 汉诺塔问题
   把问题分解，将N个盘子从A柱子以B柱子为中转放到C柱子，那么就需要先把上面的N-1个盘子先由A柱子以C柱子为中转放到B柱子，
   然后再将A柱子的那个最大的盘子放在C柱子上。
   此时N-1个盘子就在B柱子上了，此时就变成了，需要将B上的N-1个盘子以A为中转站，放到C柱子。
   问题就由N的规模变成了N-1的规模，以此类推，直到只剩下一个盘子。
*/

void Hanoi(int n, char A, char B, char C) {
	if (n == 1) {
		printf("%c-->%c\n", A, C);
		return;
	}
	//先将A上n-1个盘子放在B上
	Hanoi(n - 1, A, C, B);
	//将A上最底下的最大的那个盘子放在C上
	printf("%c-->%c\n", A, C);
	//将B上n-1个盘子转移到C上
	Hanoi(n - 1, B, A, C);
}

void test0() {
	int n = 4;
	char first = 'A', buff = 'B', target = 'C';
	int steps = 1;
	for (int i = 0; i < n; ++i) {
		steps *= 2;
	}
	printf("完成%d个盘子的汉诺塔问题，最少需要%d步，全部移动轨迹如下：\n",n ,steps - 1);
	Hanoi(n, first, buff, target);
}

int main(void)
{
	test0();
	return 0;
}