#include <nofish_header.h>
#include "tcpConnection.h"
#include "processpool.h"

int exit_pipe_fd[2];
int flag = 0;
void func(int num){
    //修改标志位，提示可以退出
    flag = 1;
}

int main(int argc, char** argv)
{
    //初始化管道：自读(select)自写（信号）管道
    pipe(exit_pipe_fd);
    //注册信号
    signal(SIGINT, func);

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
    //监听管道，目的是发现是否有2号新号触发管道，通知结束
    epoll_addfd(epoll_fd, exit_pipe_fd[0]);
    //添加本地子进程主进程监听
    for(int i = 0; i < 3; ++i) {
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
        int ready = epoll_wait(epoll_fd, event_set, 20, 0);
        if (ready == -1) {
            printf("epoll_wait\n");
            /* break; */
        } else if (ready == 0){
            /* printf("waiting information......\n"); */
        } else {
            for (int i = 0; i < ready; ++i){
                memset(buf, 0, 1024);
                int ready_fd = event_set[i].data.fd;
                //新连接到来
                if (ready_fd == connect_fd) {
                    //处理客户端
                    printf("connect_fd: %d\n", connect_fd);
                    toProcessPoolDealNet(ready_fd, process_pool, 3 );
                } else if (ready_fd == exit_pipe_fd[0]) {
                    char buf[60];
                    memset(buf, 0, 60);
                    recv(ready_fd, buf, 60, 0);
                    for(int i = 0; i < 3; i++) {
                        int close_tag = -1;
                        write_net_fd(process_pool[i].socket_local_fd, &close_tag);
                    }

                    for(int i = 0; i < 3; i++) {
                        wait(NULL);
                    }

                    printf("All son process has exited, main process exit.\n");
                    exit(0);

                } else {
                    for(int i = 0; i < 3; ++i) {
                        if(process_pool[i].socket_local_fd == ready_fd) {
                            pid_t pid;
                            recv(ready_fd, &pid, sizeof(pid), 0);
                            printf("worker pid : %d \n", pid);
                            process_pool[i]._status = FREE;
                        }
                    }
                }//if STDIN_FILENO
            }
        }
        if(flag) {
            //向管道中写入内容
            //通知退出处理
            write(exit_pipe_fd[1], "1", 1);
        } 
    }
    close(socket_fd);
    close(connect_fd);


    return 0;
}


