#include <nofish_header.h>

void tolower_by_read_and_write(const char* filename){
    int file_fd = open(filename, O_RDWR);
    ERROR_CHECK(file_fd, -1, "tolower_by_read_and_write open file %s error.\n", filename);
    char ch;
    ssize_t ret;
    while ((ret = read(file_fd, &ch, 1)) != 0) {
        ch = tolower(ch);
        lseek(file_fd, -1, SEEK_CUR);
        //注意，调用write函数后指针位置也是会往后移动一个
        write(file_fd, &ch, 1);
    }
    close(file_fd);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 2);
    tolower_by_read_and_write(argv[1]);
    return 0;
}


