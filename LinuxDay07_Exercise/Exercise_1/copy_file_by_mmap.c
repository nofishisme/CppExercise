#include <nofish_header.h>

#define BUFF_SIZE (1024 * 1024 * 2)

void file_copy(const char* dest_file, const char* src_file){
    int src_fd = open(src_file, O_RDONLY);
    ERROR_CHECK(src_fd, -1, "file_copy open file %s error.\n",src_file);
    int dest_fd = open(dest_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        fprintf(stderr, "file_copy open file %s error.\n", dest_file);
        close(src_fd);
        exit(-1);
    }
    //使用stat结构体获取文件大小
    struct stat statbuff;
    fstat(src_fd, &statbuff);
    /* off_t copy_size = lseek(src_fd, 0, SEEK_END); */
    off_t copy_size = statbuff.st_size;
    printf("src_file size is: %ld\n", copy_size);
    int ret = ftruncate(dest_fd, copy_size);
    ERROR_CHECK(ret, -1, "%s ftruncate.\n", dest_file);

    off_t bytes_copyed = 0;

    while (bytes_copyed < copy_size) {
        //1.计算当前读入的字节数是否满足BUFF_SIZE大小
        off_t copy_cur_size = 
            (copy_size - bytes_copyed < BUFF_SIZE) ? 
            copy_size - bytes_copyed : 
            BUFF_SIZE;
        //2.创建src_file和dest_file映射文件
        printf("copy_cur_size size is: %ld\n", copy_cur_size);
        printf("bytes_copyed size is: %ld\n", bytes_copyed);
        void *src_mmp = mmap(NULL, 
                             copy_cur_size, 
                             PROT_READ, 
                             MAP_SHARED, 
                             src_fd, 
                             bytes_copyed);
        ERROR_CHECK(src_mmp, MAP_FAILED, "%s mmap error.\n",src_file);
        void *dest_mmp = mmap(NULL, 
                              copy_cur_size, 
                              PROT_READ | PROT_WRITE, 
                              MAP_SHARED, 
                              dest_fd, 
                              bytes_copyed);
        ERROR_CHECK(dest_mmp, MAP_FAILED, "%s mmap error.\n",dest_file);
        //3.使用memcpy进行源映射文件到目的映射文件的拷贝，这是核心逻辑
        memcpy(dest_mmp, src_mmp, copy_cur_size);
        //4.回收mmap分配的内存映射
        munmap(src_mmp, copy_cur_size);
        munmap(dest_mmp, copy_cur_size);
        //修改已经复制的字节总数
        bytes_copyed += copy_cur_size;
    }
    close(src_fd);
    close(dest_fd);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 3);

    file_copy(argv[1], argv[2]);

    return 0;
}


