#include <nofish_header.h>
#include "tcpConnection.h"

//初始化服务端套接字监听
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

//添加连接监听
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

//删除一个连接监听
int epoll_delfd(int epoll_fd, int file_fd){
    //创建epoll监听事件
    struct epoll_event evt;
    memset(&evt, 0, sizeof(evt));
    evt.events = EPOLLIN;
    evt.data.fd = file_fd;
    //将epoll事件加入监听集合
    int res_ctl = epoll_ctl(epoll_fd, EPOLL_CTL_DEL, file_fd, &evt);
    ERROR_CHECK(res_ctl, -1, "epoll_addfd epoll_ctl1\n");

    return 0;
}

//处理新连接
int handle_new_connection(int epoll_fd, int socket_fd){
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
    //设置新连接为非阻塞
    /* int flags = fcntl(peerfd, F_GETFL); */
    /* flags |= O_NONBLOCK; */
    /* fcntl(peerfd, F_SETFL, flags); */
    //将新连接的文件描述符加入到监听的epoll
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.fd = peerfd;
    event.events = EPOLLIN | EPOLLET;
    int res = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, peerfd, &event);
    ERROR_CHECK(res, -1, "epoll_delfd epoll_ctl.\n");

    return peerfd;

}

//处理客户端发来的请求
int handle_message(int net_fd){
    //接受客户端发来的文件长度
    off_t filename_len;
    int ret;
    ret = recvn(net_fd, &filename_len, sizeof(filename_len));
    if(ret == 0){
        printf("fd %d has closed.\n", net_fd);
        close(net_fd);
        return -1;
    }
    char filename[257];
    //读取下载文件名
    memset(filename, 0, 256);
    recvn(net_fd, filename, filename_len);
    printf("recv filename:%s \n", filename);

    //发送文件名长度和文件名到客户端
    sendn(net_fd, &filename_len, sizeof(filename_len));
    sendn(net_fd, filename, filename_len);
    //服务器传输文件
    int file_fd = open(filename, O_RDONLY);
    //打开文件失败
    if(file_fd == -1){
        printf("file %s not exist.\n", filename);
        off_t size = 3;
        sendn(net_fd, &size, sizeof(off_t));
        sendn(net_fd, "404", size);
        return -1;
    }

    //打开文件成功，发送文件长度和文件内容
    struct stat file_stat;
    fstat(file_fd, &file_stat);
    //发送文件长度
    off_t file_size = file_stat.st_size;
    sendn(net_fd, &file_size, sizeof(file_size));
    //发送文件数据
    char buff[4096];
    off_t has_send = 0;
    while(has_send < file_size) {
        int ret = file_size - has_send < 4096 ? file_size - has_send : 4096;
        int read_count = read(file_fd, buff, ret);
        int send_count = sendn(net_fd, buff, read_count);
        //网络传输可能丢失数据
        /* lseek(file_fd, read_count - send_count, SEEK_CUR); */
        has_send += send_count;
    }
    close(file_fd);
    return has_send;
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
