#include <nofish_header.h>

#define CONNECTION_LIMIT 10


int initTcpSocket(int *socket_fd, const char *ip, const char *port){
      *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
      ERROR_CHECK(*socket_fd, -1, "socket\n");

      //构建struct sockaddr类型
      struct sockaddr_in socket_addr;
      memset(&socket_addr, 0, sizeof(socket_addr));
      //选择ipv4协议族
      socket_addr.sin_family = AF_INET;
      //ip点分十进制转换为网络字节序
      socket_addr.sin_addr.s_addr = inet_addr(ip);
      //端口号转换为网络字节序的大端模式
      socket_addr.sin_port = htons(atoi(port));

      //连接服务器
      int res = connect(*socket_fd, (struct sockaddr *)&socket_addr, sizeof(socket_addr));
      ERROR_CHECK(res, -1, "client connection.\n");
      return 0;

  }

int main(int argc, char** argv)
{
    const char *server_ip = "192.168.37.128";
    const char *server_port = "8080";

    int socket_fd;
    initTcpSocket(&socket_fd, server_ip, server_port);

    fd_set set;

    char buff[1024];
    while(1) {

        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(socket_fd, &set);

        select(5, &set, NULL, NULL, NULL);

        if(FD_ISSET(socket_fd, &set)) {
            memset(buff, 0, 1024);
            int ret = recv(socket_fd, buff, 1024, 0);
            if(ret == 0) {
                printf("stop more than 30s, disconnect......\n");
                break;
            }
            printf("%s", buff);
        }
        if(FD_ISSET(STDIN_FILENO, &set)) {
            memset(buff, 0, 1024);
            int read_count = read(STDIN_FILENO, buff, 1024);
            if(read_count <= 0) {
                printf("read_count.\n");
            } else {
                send(socket_fd, buff, read_count, 0);
            }
        }
    }
    close(socket_fd);
    return 0;
}


