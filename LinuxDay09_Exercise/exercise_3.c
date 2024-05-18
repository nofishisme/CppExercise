#include <nofish_header.h>


int main(int argc, char** argv)
{
    int pipe_fd = open("1.pipe", O_RDWR);
    char buff_write[4096] = {1};
    char buff_read[1024];
    int count = 0;

    fd_set read_set;
    fd_set write_set;

    while(1) {
        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
        FD_SET(pipe_fd, &read_set);
        FD_SET(pipe_fd, &write_set);

        select(10, &read_set, &write_set, NULL, NULL);
        count++;
        printf("*************** 第 %d 次***************\n", count);
        if(FD_ISSET(pipe_fd, &read_set)) {
            int read_count = read(pipe_fd, buff_read, 1024);
            printf("read_count: %d\n", read_count);
        }
        if(FD_ISSET(pipe_fd, &write_set)) {
            int write_count = write(pipe_fd, buff_write, 4096);
            printf("write_count: %d\n", write_count);
        }

        sleep(2);
    }
    close(pipe_fd);
    return 0;
}


