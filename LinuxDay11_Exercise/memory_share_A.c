#include <nofish_header.h>

void memshare(void){
    //generate a unique key
    key_t key = ftok("../LinuxDay11_Exercise", 10);
    ERROR_CHECK(key, -1, "memshare ftok error.\n");
    //generate one shared memory segment
    int share_fd = shmget(key, 4096, 0666 | IPC_CREAT);
    ERROR_CHECK(share_fd, -1, "memshare shmget error.\n");
    
    //map share memory to current progress
    char *share_mem = (char *)shmat(share_fd, NULL, 0);
    sprintf(share_mem, "How are you\n");
    shmdt(share_mem);
}

int main(int argc, char** argv)
{
    memshare();
    return 0;
}



