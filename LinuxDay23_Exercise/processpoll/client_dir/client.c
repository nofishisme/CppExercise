#include <nofish_header.h>

//发送n个字符
int sendn(int fd, const void * buff, int len);
//接受n个字符
int recvn(int fd, void * buff, int len);

//发送一行数据，不发送换行符，返回值是发送的数据数目
int sendline(int fd, const void *buff);
//接受一行数据，接受换行符，返回值是发送的数据数目
int sendline(int fd, const void *buff);

int main(int argc, char** argv)
{
    const char *sourceIP = "192.168.37.128";
    const char *sourcePort = "8080";

    //获取套接字
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(socket_fd, -1, "socket\n");

    //构建struct sockaddr类型
    struct sockaddr_in client_socket_addr;
    memset(&client_socket_addr, 0, sizeof(client_socket_addr));
    //选择ipv4协议族
    client_socket_addr.sin_family = AF_INET;
    //ip点分十进制转换为网络字节序
    client_socket_addr.sin_addr.s_addr = inet_addr(sourceIP);
    //端口号转换为网络字节序的大端模式
    client_socket_addr.sin_port = htons(atoi(sourcePort));

    //客户端向服务器发起连接请求
    int res_connect = connect(socket_fd, 
                              (struct sockaddr *)&client_socket_addr,
                              sizeof(client_socket_addr));
    ERROR_CHECK(res_connect, -1, "connect");

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
    read_event.data.fd = socket_fd;
    //将epoll事件加入监听集合
    int res_ctl1 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &stdin_event);
    ERROR_CHECK(res_ctl1, -1, "epoll_ctl1\n");
    int res_ctl2 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &read_event);
    ERROR_CHECK(res_ctl2, -1, "epoll_ctl1\n");

    //接受数据的缓冲区
    char buf[1024];

    while(1){
        //接受监听就绪事件集合的数组
        struct epoll_event event_set[2];
        //监听就绪
        int ready = epoll_wait(epoll_fd, event_set, 2, -1);
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
                    //发送文件长度和文件内容
                    send(socket_fd, buf, read_count, 0);
                }//if STDIN_FILENO
                if(reayd_fd == socket_fd) {
                    memset(buf, 0, 1024);
                    int read_count = recv(socket_fd, buf, 1024, 0);
                    if(read_count == 0) {
                        printf("server disconnect......\n");
                        exit(1);
                    }//if read_count
                    printf("server: %s", buf);
                }//if STDIN_FILENO
            }
        }
    }
    close(socket_fd);
    return 0;
}

//发送n个字节
int sendn(int fd, const void * buff, int len)
{
    int left = len;
    const char * pbuf = (const char*)buff;
    while(left > 0) {
        int ret = send(fd, pbuf, left, 0);
        if(ret < 0  && errno == EINTR) {
            continue;
        }
        pbuf += ret;
        left -= ret;
    }
    return len - left;
}
//接收n个字节
int recvn(int fd, void * buff, int len)
{
    int left = len;
    char * pbuf = (char*)buff;
    while(left > 0) {
        int ret = recv(fd, pbuf, left, 0);
        if(ret == 0) {
            //连接断开
            break;
        } else if(ret < 0  && errno == EINTR) {
            continue;
        }
        pbuf += ret;
        left -= ret;
    }
    return len - left;
}
