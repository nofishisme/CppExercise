#include <nofish_header.h>

#define CONNECTION_LIMIT 10

typedef struct connection_s{
    int conection_fd;
    bool is_alive;
    time_t the_time;
}chat_connect;

//发送n个字符
int sendn(int fd, const void * buff, int len);
//接受n个字符
int recvn(int fd, void * buff, int len);

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

int epoll_addfd(int epoll_fd, int file_fd){
    //创建epoll监听事件
    struct epoll_event evt;
    memset(&evt, 0, sizeof(evt));
    evt.events = EPOLLIN;
    evt.data.fd = file_fd;
    //将epoll事件加入监听集合
    int res_ctl = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, file_fd, &evt);
    ERROR_CHECK(res_ctl, -1, "epoll_addfd epoll_ctl1\n");

    return 0;
}

int epoll_delfd(int epoll_fd, int file_fd){
    //创建epoll监听事件
    struct epoll_event evt;
    memset(&evt, 0, sizeof(evt));
    evt.events = EPOLLIN;
    evt.data.fd = file_fd;
    //将epoll事件从监听集合删除
    int res_ctl = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, file_fd, &evt);
    ERROR_CHECK(res_ctl, -1, "epoll_delfd epoll_ctl1\n");

    return 0;

}

int handle_new_connection(chat_connect * connection_set, int epoll_fd, int socket_fd){
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
    //将新连接的文件描述符加入到监听的epoll
    epoll_addfd(epoll_fd, peerfd);
    //加入到连接队列当中
    for(int i = 0; i < CONNECTION_LIMIT; i++){
        if(connection_set[i].is_alive == false) {
            connection_set[i].conection_fd = peerfd;
            connection_set[i].is_alive = true;
            break;
        }
    }

    return peerfd;
}

//处理服务器标准输入
int handle_stdin(chat_connect * connection_set){
    char buf[1024];
    memset(buf, 0, 1024);
    int ret = read(STDOUT_FILENO, buf, 1024);
    if(ret <= 0) {
        printf("stdin\n");
        return -1;
    }

    //向所有客户端广播消息
    for(int i = 0; i < CONNECTION_LIMIT; i++) {
        if(connection_set[i].is_alive) {
            send(connection_set[i].conection_fd, buf, strlen(buf), 0);
        }
    }

    return 0;
}


int handle_message(chat_connect *connection_set, int epoll_fd, int connection_fd){
    char buf[1024];
    memset(buf, 0, 1024);
    int ret = recv(connection_fd, buf, 1024, 0);
    if (ret == 0) {
        printf("client disconnect, fd: %d\n", connection_fd);
        struct sockaddr_in peeraddr;
        socklen_t len = sizeof(peeraddr);
        getpeername(connection_fd, 
        (struct sockaddr *)&peeraddr, &len);
        printf("%s:%d has disconnected.\n",
                inet_ntoa(peeraddr.sin_addr),
                ntohs(peeraddr.sin_port));
        //从连接队列删除这个连接
        for(int i = 0; i < CONNECTION_LIMIT; i++) {
            if(connection_set[i].conection_fd == connection_fd){
                connection_set[i].is_alive = false;
            }
        }
        //从监听队列删除该连接
        epoll_delfd(epoll_fd, connection_fd);
        close(connection_fd);
        return -1;
    }
    //服务器显示某个客户端发来的消息
    printf("%s", buf);
    //群发消息
    for(int i = 0; i < CONNECTION_LIMIT; i++){
        if(connection_set[i].is_alive && 
           connection_set[i].conection_fd != connection_fd) {
            send(connection_set[i].conection_fd, buf, strlen(buf), 0);
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    const char *sourceIP = "192.168.37.128";
    const char *sourcePort = "8080";

    //初始化网络连接
    int socket_fd;
    initTcpSocket(&socket_fd, sourceIP, sourcePort);

    //创建epoll对象
    int epoll_fd = epoll_create(1);
    ERROR_CHECK(epoll_fd, -1, "epoll_create\n");
    //监听标准输入和新链接
    epoll_addfd(epoll_fd, socket_fd);
    epoll_addfd(epoll_fd, STDOUT_FILENO);

    //定义一个连接集合
    chat_connect connection_set[CONNECTION_LIMIT];
    memset(connection_set, 0, CONNECTION_LIMIT * sizeof(chat_connect));

    while(1){
        //接受监听就绪事件集合的数组
        struct epoll_event event_set[CONNECTION_LIMIT + 2];
        //监听就绪
        int ready = epoll_wait(epoll_fd, event_set, 2, -1);
        if (ready == -1) {
            printf("epoll_wait\n");
            break;
        } else if (ready == 0){
            printf("waiting information......\n");
        } else {
            for (int i = 0; i < ready; ++i){
                int ready_fd = event_set[i].data.fd;
                //新连接到来
                if (ready_fd == socket_fd) {
                    //处理新连接
                    handle_new_connection(connection_set, epoll_fd, socket_fd);
                } else if(ready_fd == STDOUT_FILENO) {
                    //处理标准输入
                    handle_stdin(connection_set);
                } else {
                    //处理客户端消息
                    handle_message(connection_set, epoll_fd, event_set[i].data.fd);
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
        if(ret < 0  && (errno == EINTR || 
                        errno == EWOULDBLOCK || 
                        errno == EAGAIN)) {
            //这个errno == EWOULDBLOCK和errno == EAGAIN表示缓冲区空了
            //errno == EINTR表示有中断到来
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
        } else if(ret < 0  && 
                  (errno == EINTR || 
                   errno == EWOULDBLOCK || 
                   errno == EAGAIN)) {
            //这个errno == EWOULDBLOCK和errno == EAGAIN表示缓冲区空了
            //errno == EINTR表示有中断到来
            continue;
        }
        pbuf += ret;
        left -= ret;
    }
    return len - left;
}
