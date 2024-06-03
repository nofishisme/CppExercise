#include <nofish_header.h>


int main(int argc, char** argv)
{
    if(fork() == 0) {
        setsid();
        chdir("/");
        umask(0);
        for(int i = 0; i < 64; i++) {
            if(i == 1) {
                continue;
            }
            close(i);
        }
        int count = 0;
        while(count <= 60) {
            count++;
            printf("This is a protect process. run %d/64 times\n",count);
            sleep(30);
        }
    }
    return 0;
}


