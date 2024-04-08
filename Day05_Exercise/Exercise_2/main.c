#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

int winCount = 0, loseCount = 0;
int running(void);
void playgame(void);
void askPlay(char *);

void rollDiceGame() {
	char play;
	printf("========***Welcome to Rollinng Dice Game***========\n");
	do {
		playgame();//玩一次游戏
		askPlay(&play);//询问是否继续玩游戏
	} while (play == 'y' || play == 'Y');//判断是否继续玩游戏
	printf("Wins: %d  Losses: %d", winCount, loseCount);
}

void test0() {
	rollDiceGame();
}

int main(void)
{
	test0();
	return 0;
}

int running(void) {
	srand(time(NULL));
	int point = rand() % 6 + 1 + rand() % 6 + 1;
	for (int i = 0; i < 1; ++i) {
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf(".");
		Sleep(500);
		printf("\r");
	}
	return point;
}

void playgame(void) {
	int point = running(), target = point;
	printf("You rolled:%d\n", point);
	if (point == 7 || point == 11) {
		printf("You win!\n");
		winCount++;
	}
	else if (point == 2 || point == 3 || point == 12) {
		printf("You lose!\n");
		loseCount++;
	}
	else {
		printf("You point is %d\n", target);
		point = running();;
		while (point != target && point != 7) {
			printf("You rolled:%d\n", point);
			point = running();
		}
		if (point == target) {
			printf("You rolled:%d\n", point);
			printf("You win!\n");
			winCount++;
		}
		else {
			printf("You rolled:%d\n", point);
			printf("You lose!\n");
			loseCount++;
		}
	}
}

void askPlay(char *play) {
	printf("\nPlay again?(y/Y means continue)");
	scanf(" %c", play);
}