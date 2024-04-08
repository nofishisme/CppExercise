#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

/* 汉诺塔问题
   把问题分解，将N个盘子从A柱子以B柱子为中转放到C柱子，那么就需要先把上面的N-1个盘子先由A柱子以C柱子为中转放到B柱子，
   然后再将A柱子的那个最大的盘子放在C柱子上。
   此时N-1个盘子就在B柱子上了，此时就变成了，需要将B上的N-1个盘子以A为中转站，放到C柱子。
   问题就由N的规模变成了N-1的规模，以此类推，直到只剩下一个盘子。

   扩展
   对于n个盘子的汉诺塔问题，给定一个整数m，要求在控制台打印出m + 1步的移动轨迹。
*/

void Hanoi(int n, char A, char B, char C, int* count, int m) {
	//已经计数到目标步数，退出函数
	if ((*count) >= (m + 1))
		return;
	if (n == 1) {
		//有效的一步，进行步数统计
		(*count)++;
		if ((*count) == (m + 1)) {
			printf("%c --> %c\n", A, C);
		}
		return;
	}
	Hanoi(n - 1, A, C, B, count, m);
	//有效的一步，进行步数统计
	(*count)++;
	if ((*count) == (m + 1)) {
		printf("%c --> %c\n", A, C);
		return;
	}
	Hanoi(n - 1, B, A, C, count, m);
}

void playHanoigame(int nums, int step) {
	char first = 'A', buff = 'B', m = 'C';
	int count = 0;
	printf("%d个盘子的汉诺塔问题，第%d步的移动轨迹是：", nums, step + 1);
	Hanoi(nums, first, buff, m, &count, step);
}

void test0() {
	playHanoigame(2, 2);
	playHanoigame(3, 2);
	playHanoigame(4, 10);
}

int main(void)
{
	test0();
	return 0;
}