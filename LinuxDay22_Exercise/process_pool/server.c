#include <nofish_header.h>
#include "tcpConnection.h"
#include "processpool.h"

int main(int argc, char** argv)
{
    const char *sourceIP = "192.168.37.128";
    const char *sourcePort = "8080";

    worker_process_t process_pool[3];
    initprocesspool(process_pool, 3);

    //初始化网络连接
    int socket_fd;
    initTcpSocket(&socket_fd, sourceIP, sourcePort);


    //创建epoll对象
    int epoll_fd = epoll_create(1);
    ERROR_CHECK(epoll_fd, -1, "epoll_create\n");
    //监听新链接
    /* epoll_addfd(epoll_fd, STDIN_FILENO); */
    //添加本地子进程主进程监听
    for(int i = 0; i < 3; ++i) {
        printf("fd %d is : %d\n", i, process_pool[i].socket_local_fd);
        printf("status %d is : %d\n", i, process_pool[i]._status);
        epoll_addfd(epoll_fd, process_pool[i].socket_local_fd);
    }
    //接受客户端请求
    int connect_fd = handle_new_connection(epoll_fd, socket_fd);

    //接受数据的缓冲区
    char buf[1024];

    while(1){
        //接受监听就绪事件集合的数组
        struct epoll_event event_set[20];
        //监听就绪
        int ready = epoll_wait(epoll_fd, event_set, 20, -1);
        if (ready == -1) {
            printf("epoll_wait\n");
            break;
        } else if (ready == 0){
            printf("waiting information......\n");
        } else {
            for (int i = 0; i < ready; ++i){
                memset(buf, 0, 1024);
                int ready_fd = event_set[i].data.fd;
                //新连接到来
                if (ready_fd == connect_fd) {
                    //处理客户端
                    printf("connect_fd: %d\n", connect_fd);
                    toProcessPoolDealNet(ready_fd, process_pool, 3 );
                } else {
                    for(int i = 0; i < 3; ++i) {
                        if(process_pool[i].socket_local_fd == ready_fd) {
                            pid_t pid;
                            recv(ready_fd, &pid, sizeof(pid), 0);
                            printf("worker pid: %d\n", pid);
                            process_pool[i]._status = FREE;
                        }
                    }
                }//if STDIN_FILENO
            }
        }
    }
    close(socket_fd);
    close(connect_fd);


    return 0;
}


