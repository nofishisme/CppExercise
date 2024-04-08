#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

/* 4种花色，使用一个包含四个字符的数组来存储
   13种点数，使用一个人包含13个字符的数组来存储
   随机发牌使用到随机数
   每次发牌之后，牌的总数应该要少一张，不应该发重复的牌
   使用一个二维数组来存储每张牌是否已经发出。
*/
void distributeCards() {
	int nums = 0;//需要的手牌数量
	//初始化花色数组
	char suit[4] = { 'C','D','H','S' };
	//初始化点数数组
	char point[13] = { '2','3','4,','5','6','7','8','9','T','J','Q','K','A' };
	int exist[4][13];
	//初始化发牌记录数组
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			exist[i][j] = 0;
		}
	}
	srand(time(NULL));
	printf("请输入您需要的手牌数量：\n");
	scanf("%d", &nums);
	//发牌
	printf("发牌中.");
	Sleep(500);
	printf("\b..");
	Sleep(500);
	printf("\b\b...");
	Sleep(500);
	printf("\b\b\b....");
	Sleep(500);
	printf("\r");
	printf("您的手牌是：\n");
	for (int k = 0; k < nums; k++) {
		int s = rand() % 4;
		int p = rand() % 13;//发随机花色和点数
		while (exist[s][p] == 1) {
			s = rand() % 4;//已经发出相同花色了，继续发新的随机花色和点数
			p = rand() % 13;
		}
		exist[s][p] = 1;
		printf("%c%c      ", suit[s], point[p]);
	}
}
void test0() {
	distributeCards();
}

int main(void)
{
	test0();
	return 0;
}