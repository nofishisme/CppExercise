#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void menu() {
	printf("======= ���˳����˵� =======\n");
	printf("0. ����˻����\n");
	printf("1. ���˻��ϴ�Ǯ\n");
	printf("2. ���˻���ȡǮ\n");
	printf("3. ��ʾ��ǰ���\n");
	printf("4. �˳�����\n");
	printf("��ѡ�������0 - 4����\n");
}

void clearAccount(double *balance) {
	*balance = 0;
	printf("�˻��������գ�\n");
	printf("��ǰ�˻���%.2lf\n", *balance);
}

void deposit(double *balance) {
	double money = 0;
	printf("������Ҫ����Ľ�\n");
	scanf("%lf", &money);
	*balance += money;
	printf("�ɹ���%.2lf\n", money);
	printf("��ǰ�˻���%.2lf\n", *balance);
}

void withdraw(double *balance) {
	double money = 0;
	printf("������Ҫȡ���Ľ�\n");
	scanf("%lf", &money);
	if (*balance - money < 0) {
		printf("����ȡ����ܴ���������\n");
	}
	else {
		*balance -= money;
		printf("�ɹ�ȡ�%.2lf\n", money);
		printf("��ǰ�˻���%.2lf\n", *balance);
	}
}

void display(double *balance) {
	printf("�˻�����ǣ�%.2lf\n", *balance);
}

void test0() {
	double balacne = 0;
	int select;
	menu();
	scanf("%d", &select);
	while (select != 4) {
		switch (select)
		{
		case 0:
			clearAccount(&balacne);
			break;
		case 1:
			deposit(&balacne);
			break;
		case 2:
			withdraw(&balacne);
			break;
		case 3:
			display(&balacne);
			break;
		default:
			break;
		}
		menu();
		scanf("%d", &select);
	}
	printf("Done!");
}

int main(void)
{
	test0();
	return 0;
}