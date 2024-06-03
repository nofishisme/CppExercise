#include <nofish_header.h>

void tolower_by_mmap(const char* filename){
    int file_fd = open(filename, O_RDWR);
    ERROR_CHECK(file_fd, -1, "tolower %s open error.\n", filename);
    int buf = 1024;
    off_t file_size = lseek(file_fd, 0, SEEK_END);
    off_t bytes_processed = 0;
    while (bytes_processed < file_size) {
        off_t read_bytes = (file_size - bytes_processed < buf) ?
            file_size - bytes_processed : buf;
        char *file_mmp = (char*)mmap(NULL, 
                              read_bytes, 
                              PROT_READ | PROT_WRITE,
                              MAP_SHARED,
                              file_fd,
                              bytes_processed);
        //将大写字母转变为小写字母
        for (int i = 0; i < read_bytes; ++i) {
            file_mmp[i] = tolower(file_mmp[i]);
        }
        munmap(file_mmp, read_bytes);
        bytes_processed += read_bytes;
    }
    close(file_fd);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 2);
    tolower_by_mmap(argv[1]);
    return 0;
}


