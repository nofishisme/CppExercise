#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void menu() {
	printf("======= 记账程序账单 =======\n");
	printf("0. 清空账户余额\n");
	printf("1. 往账户上存钱\n");
	printf("2. 从账户上取钱\n");
	printf("3. 显示当前余额\n");
	printf("4. 退出程序\n");
	printf("请选择操作（0 - 4）：\n");
}

void clearAccount(double *balance) {
	*balance = 0;
	printf("账户余额已清空！\n");
	printf("当前账户余额：%.2lf\n", *balance);
}

void deposit(double *balance) {
	double money = 0;
	printf("请输入要存入的金额：\n");
	scanf("%lf", &money);
	*balance += money;
	printf("成功存款：%.2lf\n", money);
	printf("当前账户余额：%.2lf\n", *balance);
}

void withdraw(double *balance) {
	double money = 0;
	printf("请输入要取出的金额：\n");
	scanf("%lf", &money);
	if (*balance - money < 0) {
		printf("错误，取款金额不能大于余额！！！\n");
	}
	else {
		*balance -= money;
		printf("成功取款：%.2lf\n", money);
		printf("当前账户余额：%.2lf\n", *balance);
	}
}

void display(double *balance) {
	printf("账户余额是：%.2lf\n", *balance);
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