#include <nofish_header.h>


int main(int argc, char** argv)
{
    sigset_t set, cur;
    sigemptyset(&set);
    sigemptyset(&cur);
    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, NULL);
    sleep(5);
    sigpending(&cur);
    for(int i = 63; i >= 0; --i) {
        if(sigismember(&cur, i)) {
            printf("1");
        }else{
            printf("0");
        }
    }
    printf("\n");
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    return 0;
}


