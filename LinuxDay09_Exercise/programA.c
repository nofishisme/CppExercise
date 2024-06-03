#include <nofish_header.h>


int main(int argc, char** argv)
{
    printf("1.Helloworld\n");
    int pipe_write_fd = open("1.pipe", O_WRONLY);
    int pipe_read_fd = open("2.pipe", O_RDONLY);
    char str[] = "2.Helloworld\n";
    write(pipe_write_fd, str, strlen(str));
    
    char buff[64];
    memset(buff, 0, 64);
    int read_count = read(pipe_read_fd, buff, 64);
    write(STDOUT_FILENO, buff, read_count);

    close(pipe_read_fd);
    close(pipe_write_fd);
    return 0;
}


