#include <nofish_header.h>


void func(int sig_val){
    printf("both disconnecting......\n");
    exit(0);
}

int main(int argc, char** argv)
{

    signal(SIGUSR1, func);

    int read_fd = open("1.pipe",O_RDONLY);
    ERROR_CHECK(read_fd, -1, "read_fd open error\n");
    int write_fd = open("2.pipe",O_WRONLY);
    ERROR_CHECK(write_fd, -1, "write_fd open error\n");

    pid_t clientB_pid = getpid();
    pid_t clientA_pid;
    write(write_fd, &clientB_pid, sizeof(clientB_pid));
    read(read_fd, &clientA_pid, sizeof(clientA_pid));
    printf("clientA_pid: %d\n", clientA_pid);
    printf("clientB_pid: %d\n", clientB_pid);

    /* printf("initial......\n"); */
    /* sleep(2); */

    char buff[4096];
    fd_set set;

    while(1) {

        FD_ZERO(&set);
        FD_SET(read_fd, &set);
        FD_SET(STDIN_FILENO, &set);

        select(10, &set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &set)) {
            memset(buff, 0, 4096);
            int read_count = read(STDIN_FILENO, buff, 4096);
            if(read_count <= 0) {
                printf("input error.\n");
                break;
            }
            if(strcmp(buff,"1\n") == 0){
                //输入1，需要退出程序
                kill(clientA_pid,SIGUSR1);
                kill(clientB_pid,SIGUSR1);
            }else{
                write(write_fd, buff, read_count);
            }
        }
        if(FD_ISSET(read_fd, &set)){
            memset(buff, 0, 4096);
            int read_count = read(read_fd, buff, 4096);
            /* if(read_count == 0) { */
            /*     printf("clientA is disconnected......\n"); */
            /*     break; */
            /* } */
            if(read_count <= 0) {
                continue;
            }
            write(STDOUT_FILENO, buff, read_count);
        }
    }

    close(write_fd);
    close(read_fd);

    return 0;
}


