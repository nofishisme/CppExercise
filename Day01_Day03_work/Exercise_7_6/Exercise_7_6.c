//����һ���ǿյ���������nums����֪������Ԫ��ֻ������һ�Σ�����Ԫ�ؾ��������Σ���ô�����ҳ�������ֻ����һ�ε�Ԫ�ء�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void findTwoSingleElem(int arr[], int n) {
	int bitmask = 0,elem1 = 0, elem2 = 0;
	for (int i = 0; i < n; ++i) {
		bitmask ^= arr[i];
	}
	int diff = bitmask & (-bitmask);
	for (int j = 0; j < n; ++j) {
		if (arr[j] & diff != 0)//������ľ���˵���ܿ�����2����Ԫ������һ��Ԫ�أ�Ȼ�������������Ԫ�ؽ���������õ�һ������2��Ԫ���е���һ����
			elem1 ^= arr[j];
	}
	elem2 = bitmask ^ elem1;
	printf("��һ��Ԫ���ǣ�%d\n", elem1);
	printf("�ڶ���Ԫ���ǣ�%d\n", elem2);
}

void test0() {
	int nums[] = { 1,1,2,2,3,9,3,9,8,8,7,6,5,5 };
	for (int i = 0; i < 14; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
	findTwoSingleElem(nums, 14);
}

int main(void)
{
	test0();
	return 0;
}