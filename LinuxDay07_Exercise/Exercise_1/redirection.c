#include <nofish_header.h>

//重定向标准输出到文件
void redirection_output_to_file(const char* filename){
    printf("喜洋洋，美羊羊，懒羊羊，沸羊羊\n");
    close(STDOUT_FILENO);
    int file_fp = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(file_fp, -1, "redirection_output_to_file open %s error.\n", filename);
    printf("慢羊羊，软绵绵，红太狼，灰太狼！！！\n");
}
//重定向标准输入到文件
void redirection_input_from_file(const char* filename){
    char buff[1024];
    fgets(buff, 1024, stdin);
    printf("string from stdin is: %s", buff);
    close(STDIN_FILENO);
    int file_fp = open(filename, O_RDONLY);
    ERROR_CHECK(file_fp, -1, "redirection_input_from_file open %s error.\n", filename);
    fgets(buff, 1024, stdin);
    printf("string from file is: %s", buff);
    close(file_fp);
}

//实现在标准输出重定向到文件，复原，再重定向到文件的反复横跳
void redirection_cycle(const char* filename){
    //给一个用于备份的文件描述符
    int buf_fd = 9;
    //打开文件流
    int file_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(file_fd, -1, "open");
    for(int i = 0; i < 5; ++i) {
        printf("喜洋洋，美羊羊，懒羊羊，沸羊羊\n");
        //备份标准输出流文件对象
        int ret1 = dup2(STDOUT_FILENO, buf_fd);
        ERROR_CHECK(ret1, -1, "dup2");
        //标准输出重定向到文件
        int ret2 = dup2(file_fd, STDOUT_FILENO);
        ERROR_CHECK(ret2, -1, "dup2");
        printf("慢羊羊，软绵绵，红太狼，灰太狼！！！\n");

        //恢复标准输出流对象
        dup2(buf_fd, STDOUT_FILENO);
    }
    close(buf_fd);
    close(file_fd);

}

void redirection_server_log(void){
    fprintf(stderr,"redirection_server_log.\n");
    int fd = open("server.log", O_WRONLY | O_CREAT | O_APPEND, 0666);
    ERROR_CHECK(fd, -1, "redirection_server_log open.\n");
    dup2(fd, STDERR_FILENO);
    fprintf(stderr, "redirection_input_from_file.\n");
    fprintf(stderr, "redirection_input_from_file.\n");
    fprintf(stderr, "redirection_input_from_file.\n");
    fprintf(stderr, "redirection_input_from_file.\n");
    close(fd);
    close(STDERR_FILENO);
}

int main(int argc, char** argv)
{
    /* ARGS_CHECK(argc, 2); */
    /* redirection_output_to_file(argv[1]); */
    /* redirection_input_from_file(argv[1]); */
    /* redirection_cycle(argv[1]); */
    redirection_server_log();
    return 0;
}


