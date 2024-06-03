#include <nofish_header.h>


void recv(){
    int pipe_fd = open("1.pipe", O_RDONLY);

    //解析文件名
    long filename_len;
    read(pipe_fd, &filename_len, sizeof(filename_len));
    char filename[64];
    memset(filename, 0, 64);//存名字缓冲区置0
    read(pipe_fd, filename, filename_len);

    mkdir("copy",0775);
    chdir("copy");

    int file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    //解析文件长度
    long file_len;
    read(pipe_fd, &file_len, sizeof(file_len));
    ftruncate(file_fd, file_len);

    char buff[1024];
    long read_count;
    while((read_count = read(pipe_fd, buff, 1024)) > 0) {
        write(file_fd, buff, read_count);
    }
    close(pipe_fd);
    close(file_fd);
}

int main(int argc, char** argv)
{
    recv();
    return 0;
}


