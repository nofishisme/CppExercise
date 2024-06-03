#include <nofish_header.h>

void copy_file(const char* dest_file, const char* src_file) {
    int ret_read = open(src_file, O_RDONLY);
    ERROR_CHECK(ret_read, -1, "copy_file open src_fil error.\n");
    int ret_write = open(dest_file,O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (ret_write == -1) {
        perror("copy_file open dest_file error.\n");
        close(ret_read);
        exit(-1);
    }
    char buff[1024];
    int read_count;
    while ((read_count = read(ret_read, buff, 1024)) > 0) {
        write(ret_write, buff, read_count);
    }
    close(ret_read);
    close(ret_write);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 3);
    copy_file(argv[1], argv[2]);
    return 0;
}


