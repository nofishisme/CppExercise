#include <nofish_header.h>


int main(int argc, char** argv)
{
    key_t key = ftok("../LinuxDay11_Exercise", 11);
    ERROR_CHECK(key, -1, "exercise_4.c ftok error.\n");
    int share_fd = shmget(key, 4096, 0666 | IPC_CREAT);
    ERROR_CHECK(share_fd, -1, "exercise_4.c shmget error.\n");
    int* share_mem = (int*)shmat(share_fd, NULL, 0);
    share_mem[0] = 0;
    printf("At the begin, the number in share_mem is: %d\n", share_mem[0]);
    if(fork() == 0) {
        int count = 10000000;
        while(count > 0) {
            share_mem[0]++;
            count--;
        }
        printf("child --> The number in share_mem is: %d\n", share_mem[0]);
    }else {
        int count = 10000000;
        while(count > 0) {
            share_mem[0]++;
            count--;
        }
        printf("main --> The number in share_mem is: %d\n", share_mem[0]);
    }
    return 0;
}



