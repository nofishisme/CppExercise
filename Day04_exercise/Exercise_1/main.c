//��дһ������Ҫ���û�����¼��ʮ��ѧ�������ĳɼ�(�ٷ���)��Ȼ��洢��һ��һά�����С�
// ������ȫ���ƽ���ɼ�����߷ֺ���ͷ֣�����ӡ������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define STUDENT_NUM 10

void test0() {
	int score[STUDENT_NUM] = { 0 };
	int maxScore = 0, minScore = 100;
	int sum = 0,avrage = 0;
	for (int i = 0; i < STUDENT_NUM; ++i) {
		printf("����� %d ��ѧ���ĳɼ���\n", i + 1);
		scanf("%d", score + i);
		if (score[i] > maxScore) {
			maxScore = score[i];
		}
		if(score[i] < minScore) {
			minScore = score[i];
		}
		sum += score[i];
	}
	avrage = sum / STUDENT_NUM;
	printf("ȫ����߳ɼ��ǣ�%d\n", maxScore);
	printf("ȫ����ͳɼ��ǣ�%d\n", minScore);
	printf("ȫ��ƽ���ɼ��ǣ�%d\n", avrage);
}

int main(void)
{
	test0();
	return 0;
}