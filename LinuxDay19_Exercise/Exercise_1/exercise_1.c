#include <nofish_header.h>


int main(int argc, char** argv)
{
    int num = 4;
    char *p = (char *)&num;
    printf("num = %d\n", num);
    int len = sizeof(num);
    int pos = 0;
    while(pos++ < len) {
        int res = *p++;
        printf("%02d ", res);
    }
    printf("\n");
    return 0;
}


