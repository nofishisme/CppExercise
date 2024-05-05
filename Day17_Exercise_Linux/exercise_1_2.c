#include <stdio.h>
#include <ctype.h>
void countNumOfCharacter(void){
    char buff[1024];
    fgets(buff, 1024, stdin);
    char* cur = buff;
    int count_letter = 0, count_number = 0, count_space = 0;
    while (*cur != '\n'){
        if (isspace(*cur)) {
            count_space++;
        }else if (isalpha(*cur)){
            count_letter++;
        }else if (isdigit(*cur)) {
            count_number++;
        }
        cur++;
    }
    printf("字母的数量是：%d\n", count_letter);
    printf("数字的数量是：%d\n", count_number);
    printf("空格的数量是：%d\n", count_space);
}

int main()
{
    countNumOfCharacter();
    return 0;
}

