#include <nofish_header.h>


int main(int argc, char** argv)
{
    if(fork() == 0) {
        while(1) {
            printf("child pid: %d\n", getpid());
            sleep(2);
        }
    }
    printf("main process done!");
    return 0;
}


