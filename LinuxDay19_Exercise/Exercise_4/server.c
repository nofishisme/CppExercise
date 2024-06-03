#include <nofish_header.h>


int main(int argc, char** argv)
{
    const char *sourceIP = "192.168.37.128";
    const char *sourcePort = "8080";

    //获取套接字
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket\n");

    //构建struct sockaddr类型
    struct sockaddr_in server_socket_addr;
    memset(&server_socket_addr, 0, sizeof(server_socket_addr));
    //选择ipv4协议族
    server_socket_addr.sin_family = AF_INET;
    //ip点分十进制转换为网络字节序
    server_socket_addr.sin_addr.s_addr = inet_addr(sourceIP);
    //端口号转换为网络字节序的大端模式
    server_socket_addr.sin_port = ntohs(atoi(sourcePort));

    //设置端口复用
    int opt = 10;
    int res_setopt = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    ERROR_CHECK(res_setopt, -1, "setsockopt\n");

    //服务器绑定端口
    bind(socket_fd, (struct sockaddr *)&server_socket_addr, sizeof(server_socket_addr));

    //监听ip端口，等待服务器连接
    listen(socket_fd, 10);

    //接受客户端发来的连接请求；
    int connect_fd = accept(socket_fd, NULL, NULL);
    ERROR_CHECK(connect_fd, -1, "accept\n");

    //创建epoll对象
    int epoll_fd = epoll_create(1);
    ERROR_CHECK(epoll_fd, -1, "epoll_create\n");
    //创建epoll监听事件，监听标准输入和连接方的文件描述符
    struct epoll_event stdin_event, read_event;
    memset(&stdin_event, 0, sizeof(stdin_event));
    memset(&read_event, 0, sizeof(read_event));
    stdin_event.events = EPOLLIN;
    stdin_event.data.fd = STDIN_FILENO ;
    read_event.events = EPOLLIN;
    read_event.data.fd = connect_fd;
    //将epoll事件加入监听集合
    int res_ctl1 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &stdin_event);
    ERROR_CHECK(res_ctl1, -1, "epoll_ctl1\n");
    int res_ctl2 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &read_event);
    ERROR_CHECK(res_ctl2, -1, "epoll_ctl1\n");

    //接受数据的缓冲区
    char buf[1024];

    while(1){
        //接受监听就绪事件集合的数组
        struct epoll_event event_set[2];
        //监听就绪
        int ready = epoll_wait(epoll_fd, event_set, 2, 5000);
        if(ready == -1){
            printf("epoll_wait\n");
            break;
        }else if(ready == 0){
            printf("waiting information......\n");
        }else{
            for(int i = 0; i < ready; ++i){
                memset(buf, 0, 1024);
                int reayd_fd = event_set[i].data.fd;
                if(reayd_fd == STDIN_FILENO) {
                    int read_count = read(STDIN_FILENO, buf, 1024);
                    send(connect_fd, buf, read_count, 0);
                }//if STDIN_FILENO
                if(reayd_fd == connect_fd) {
                    int read_count = recv(connect_fd, buf, 1024, 0);
                    if(read_count == 0) {
                        printf("disconnect......\n");
                    }//if read_count
                    write(STDOUT_FILENO, buf, read_count);
                }//if STDIN_FILENO
            }
        }
    }
    close(socket_fd);
    close(connect_fd);

    return 0;
}


