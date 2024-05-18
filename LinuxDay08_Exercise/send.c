#include <nofish_header.h>


void send(const char* filename){
    int file_fd = open(filename, O_RDONLY);

    int pipe_fd = open("1.pipe", O_WRONLY);

    long file_len = lseek(file_fd, 0, SEEK_END);
    lseek(file_fd, 0, SEEK_SET);

    long filename_len = strlen(filename);
    //文件名字长度
    write(pipe_fd, &filename_len, sizeof(filename_len));
    //文件名字
    write(pipe_fd, filename, filename_len);
    //文件长度
    write(pipe_fd, &file_len, sizeof(file_len));
    //文件内容
    char buff[1024];
    long read_count;
    while((read_count = read(file_fd, buff, 1024)) > 0) {
        write(pipe_fd, buff, read_count);
    }
    close(file_fd);
    close(pipe_fd);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 2);
    send(argv[1]);
    return 0;
}


