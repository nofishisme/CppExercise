#include <nofish_header.h>


int main(int argc, char** argv)
{
    if(fork() == 0) {
        printf("child process pid: %d\n", getpid());
        execl("./my_la", "./my_la", ".", (char *)0);
    }
    wait(NULL);
    return 0;
}


