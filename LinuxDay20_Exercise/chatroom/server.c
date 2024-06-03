#include <nofish_header.h>

#define CONNECTION_LIMIT 10

typedef struct connection_s{
    int conection_fd;
    bool is_alive;
}chat_connect;

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

      //设置端口复用
      int opt = 10;
      int res_setopt = setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
      ERROR_CHECK(res_setopt, -1, "setsockopt\n");

      //服务器绑定端口
      bind(*socket_fd, (struct sockaddr *)&socket_addr, sizeof(socket_addr));

      //监听ip端口，等待服务器连接
      listen(*socket_fd, 10);

      return 0;

  }
int handle_new_connection(fd_set *set, int socket_fd){
      //peeraddr用于获取对端连接信息
      struct sockaddr_in peeraddr;
      socklen_t len = sizeof(peeraddr);
      int peerfd = accept(socket_fd, (struct sockaddr *)&peeraddr, &len);
      if(peerfd == -1) {
          return -1;
      }
      printf("connect a new client, peerfd: %d\n", peerfd);
      printf("%s:%d has connected.\n",
             inet_ntoa(peeraddr.sin_addr),
             ntohs(peeraddr.sin_port));
      return peerfd;
}

int main(int argc, char** argv)
{
    const char *server_ip = "192.168.37.128";
    const char *server_port = "8080";

    int socket_fd;
    initTcpSocket(&socket_fd, server_ip, server_port);

    fd_set set;

    chat_connect connection_set[CONNECTION_LIMIT];
    memset(connection_set, 0, CONNECTION_LIMIT * sizeof(chat_connect));

    char buff[1024];
    while(1) {

        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(socket_fd, &set);
        for(int i = 0; i < CONNECTION_LIMIT; ++i) {
            if(connection_set[i].is_alive) {
                FD_SET(connection_set[i].conection_fd, &set);
            }
        }
        select(20, &set, NULL, NULL, NULL);

        if(FD_ISSET(socket_fd, &set)) {
            int con_fd = handle_new_connection(&set, socket_fd);
            if(con_fd == -1) {
                printf("handle_new_connection.\n");
            } else {
                //将新连接加入到已连接集合
                for(int i = 0; i < CONNECTION_LIMIT; ++i) {
                    if(connection_set[i].is_alive == false){
                        connection_set[i].conection_fd = con_fd;
                        connection_set[i].is_alive = true;
                        break;
                    }
                }
            }
        }
        if(FD_ISSET(STDIN_FILENO, &set)) {
            memset(buff, 0, 1024);
            int read_count = read(STDIN_FILENO, buff, 1024);
            if(read_count <= 0) {
                printf("read_count.\n");
            } else {
                //向所有连接的客户端发消息
                for(int i = 0; i < CONNECTION_LIMIT; ++i) {
                    if(connection_set[i].is_alive){
                        send(connection_set[i].conection_fd, buff, read_count, 0);
                    }
                }
            }
        }
        for(int i = 0; i < CONNECTION_LIMIT; ++i) {
            if(connection_set[i].is_alive && FD_ISSET(connection_set[i].conection_fd, &set)) {
                memset(buff, 0, 1024);
                int ret = recv(connection_set[i].conection_fd, buff, 1024, 0);
                //客户端断开连接
                if(ret == 0) {
                    printf("client disconnect, fd: %d\n", connection_set[i].conection_fd);
                    struct sockaddr_in peeraddr;
                    socklen_t len = sizeof(peeraddr);
                    getpeername(connection_set[i].conection_fd, 
                                (struct sockaddr *)&peeraddr, &len);
                    printf("%s:%d has connected.\n",
                                inet_ntoa(peeraddr.sin_addr),
                                ntohs(peeraddr.sin_port));
                    close(connection_set[i].conection_fd);
                    connection_set[i].is_alive = false;
                    continue;
                }
                for(int j = 0; j < CONNECTION_LIMIT; j++) {
                    //不发给自己
                    if(i == j){
                        continue;
                    }
                    if(connection_set[j].is_alive) {
                        send(connection_set[j].conection_fd, buff, strlen(buff), 0);
                    }
                }
            } 
        }
    }
    for(int i = 0; i < CONNECTION_LIMIT; ++i) {
        if(connection_set[i].is_alive) {
            close(connection_set[i].conection_fd);
        }
    }
    close(socket_fd);
    return 0;
}


