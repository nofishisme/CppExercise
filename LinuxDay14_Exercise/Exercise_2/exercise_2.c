#include <nofish_header.h>

void *func(void *arg){
    sleep(5);
    char buf[1024];
    long file_fd = (long)arg;
    memset(buf, 0, 1024);
    read((int)file_fd, buf, 1024);
    printf("child thread read content from file: %s\n",buf);
    close((int)file_fd);
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    ARGS_CHECK(argc, 2);

    int file_fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    char str[] = "hello, nofish.\n";
    printf("main func write to file: %s\n", str);
    write(file_fd, str, strlen(str));

    lseek(file_fd, 0, SEEK_SET);

    pthread_t a_thread;
    pthread_create(&a_thread, NULL, func, (void *)(long)file_fd);
    pthread_join(a_thread, NULL);
    sleep(10);
    
    lseek(file_fd, 0, SEEK_SET);
    char buf[1024];
    memset(buf, 0, 1024);
    read(file_fd, buf, 1024);
    printf("main func read from file: %s\n", buf);
    close(file_fd);
    return 0;
}


