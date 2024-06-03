#include <nofish_header.h>


int main(int argc, char** argv)
{
    if(fork() == 0) {
        printf("child pid: %d\n", getpid());
    }
    while(1) {
        printf("main pid: %d\n", getpid());
        sleep(2);
    }
    return 0;
}


