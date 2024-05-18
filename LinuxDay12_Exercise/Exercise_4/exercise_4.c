#include <nofish_header.h>

static int count = 0;

void func(int sig_val){
    count++;
    printf("func exe %d times\n", count);
    sleep(10);
    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);
    if(sigismember(&set, 2)){
        printf("sig_value: %d in pengding\n", sig_val);
    }else{
        printf("%d not in pending\n", sig_val);
    }
}

int main(int argc, char** argv)
{
    signal(SIGINT, func);
    sleep(10);
    return 0;
}


