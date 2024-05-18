#include <nofish_header.h>


int main(int argc, char** argv)
{
    int pipe_fd[2];
    pipe(pipe_fd);
    if(fork() == 0){
        //close write, reserve read
        close(pipe_fd[1]);
        int count = 0;
        while(1) {
            char buff[1024];
            printf("child count: %d\n", ++count);
            int read_count = read(pipe_fd[0], buff, 1024);
            printf("child read_count: %d\n", read_count);
            sleep(1);
            break;
        }
        close(pipe_fd[0]);
        while(1) {
            printf("child read close.\n");
            sleep(10);
        }
    }
    //close read, reserve write
    close(pipe_fd[0]);
    sleep(5);
    printf("main func sleep 5 sec.\n");
    int count = 0;
    while(1) {
        char buff[4096];
        printf("main count: %d\n", ++count);
        int write_count = write(pipe_fd[1], buff, 4096);
        printf("main write_count: %d\n",write_count);
        sleep(10);
    }
    return 0;
}


