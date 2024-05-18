#include <nofish_header.h>

void server(){

    int nfds = 10;
    int read_fd = open("2.pipe", O_RDONLY);
    ERROR_CHECK(read_fd, -1 ,"client read_fd open.\n");
    int write_fd = open("1.pipe", O_WRONLY);
    ERROR_CHECK(write_fd, -1 ,"client write_fd open.\n");

    fd_set set;

    struct timeval time_val;
    time_val.tv_sec = 10;
    time_val.tv_usec = 0;

    char buff[1024];
    while(1) {

        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(read_fd, &set);
        

        select(nfds, &set, NULL, NULL, &time_val);

        if(FD_ISSET(STDIN_FILENO, &set)) {
            memset(buff, 0, 1024);
            int count = read(STDIN_FILENO, buff, 1024);
            if(count == 0) {
                break;
            }
            write(write_fd, buff, count);
        }

        if(FD_ISSET(read_fd, &set)) {
            memset(buff, 0, 1024);
            int count = read(read_fd, buff, 1024);
            if(count == 0) {
                printf("client is disconnected......\n");
                break;
            }
            write(STDOUT_FILENO, buff, count);
            time_val.tv_sec = 10;
            time_val.tv_usec = 0;
        }else {
            if(time_val.tv_sec <= 0) {
                printf("wait more than 10 sec. disconnect......\n");
                break;
            }
        }
    }
    close(write_fd);
    close(read_fd);
    printf("Done!\n");
}

int main(int argc, char** argv)
{
    server();
    return 0;
}


