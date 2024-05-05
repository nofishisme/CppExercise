#include <stdio.h>
#include <stdlib.h>

void printMultiplicationTable(void){
    for(int i = 1; i <= 9; ++i) {
        for(int j = 1; j <= i; j++) {
            printf("%d * %d = %2d  ", i, j, i * j);
        }
        printf("\n");
    }
}

int main()
{
    printMultiplicationTable();
    return 0;
}

