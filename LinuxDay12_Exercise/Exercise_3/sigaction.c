#include <nofish_header.h>

void func(int sig_val) {
    sigset_t set;
    sigemptyset(&set);
    sigpending(&set);
    if(sigismember(&set, 3)){
        printf("信号3处于未决状态\n");
    }else{
        printf("信号3不在未决状态\n");
    }
}

int main(int argc, char** argv)
{
    sigset_t mask_set;
    sigemptyset(&mask_set);
    sigaddset(&mask_set, 3);
    struct sigaction sig_ac;
    sig_ac.sa_handler = func;
    sig_ac.sa_mask = mask_set;
    sig_ac.sa_flags = 0 | SA_RESTART;
    sigaction(2, &sig_ac, NULL);

    char buf[1024];
    memset(buf, 0, 1024);
    int read_count = read(STDIN_FILENO, buf, 1024);
    write(STDOUT_FILENO, buf, read_count);

    return 0;
}


