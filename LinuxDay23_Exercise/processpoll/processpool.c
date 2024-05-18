#include <nofish_header.h>
#include "processpool.h"



//初始化进程池
int initprocesspool(worker_process_t *p, int num){
    ERROR_CHECK(p, NULL, "initprocesspool malloc error.\n");
    printf("num: %d\n", num);

    for(int i = 0; i < num; ++i) {
        int socket_fd[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_fd);
        pid_t tmp_pid;
        if((tmp_pid = fork()) == 0){
            close(socket_fd[1]);
            startWorker(socket_fd[0]);
        } else {
            p[i]._pid = tmp_pid;
            p[i]._status = FREE;
            p[i].socket_local_fd = socket_fd[1];
            close(socket_fd[0]);
        }
    } 

    return 0;
}

//处理连接，监听到的连接交个空闲的线程
int toProcessPoolDealNet(int net_fd, worker_process_t *p, int num){
    for(int i = 0; i < num; ++i) {
        if(p[i]._status == FREE) {
            write_net_fd(p[i].socket_local_fd, &net_fd);
            p[i]._status = BUSY;
            break;
        }
    }
    
    return 0;
}

//启动一个工作进程
int startWorker(int socket_local_fd){
    //脱离当前进程组
    printf("group id : %d\n", getpgrp());
    setpgid(0, 0);
    printf("after set, group id : %d\n", getpgrp());
    while(1) {
        int net_fd;
        read_net_fd(socket_local_fd, &net_fd);

        if(net_fd == -1) {
            //对端发送了-1，要求清理资源，退出进程的通知
            printf("son process %d clear sources and exit.\n", getpid());
            exit(0);
        }

        if(net_fd == 0) {
            //对端发送了错误的0，或者对端关闭数据发生的socket
            sleep(100);
        }
        printf("worker net_fd: %d \n", net_fd);

        //用获得的文件描述符和客户端通信
        netToClient(net_fd);

        //关闭和客户端的连接
        //这个地方只是关闭了子进程的连接，主进程那个套接字文件描述符是没有关闭的
        close(net_fd);

        //进程完成任务，通过本地socket。发送信息给主进程
        //表示连接通信已经完成，主进程修改忙状态位
        pid_t pid = getpid();
        printf("worker pid : %d \n", pid);
        send(socket_local_fd, &pid, sizeof(pid), 0);
    }
    return 0;
}

//工作进程，从本地socket中读取main进程发过来的客户端连接对象
int read_net_fd(int socket_local_fd, int *netfd){
    struct msghdr hdr;
    memset(&hdr, 0, sizeof(hdr));

    struct iovec vec[1];
    int flag = 1;
    vec[0].iov_base = &flag;
    vec[0].iov_len = sizeof(int);

    hdr.msg_iov = vec;
    hdr.msg_iovlen = 1;

    struct cmsghdr *pcmsg = (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = recvmsg(socket_local_fd, &hdr, 0);
    ERROR_CHECK(ret, -1, "read_net_fd recvmsg.\n");

    if(*(int *)hdr.msg_iov[0].iov_base == -1){
        //说明对面发送的正文是-1，表明主进程需要退出
        //关闭子进程
        *netfd = -1;
        return 0;
    }

    void *addr = CMSG_DATA(pcmsg);
    int *p_fd = (int *)addr;
    *netfd = *p_fd;

    return 0;
}

//main进程accept获得的客户端连接对象发给工作进程
int write_net_fd(int socket_local_fd, int *net_fd){
    struct msghdr hdr;
    memset(&hdr, 0, sizeof(hdr));

    //利用正文vec来传递-1
    //首先，如果使用sendmsg传送一个-1的文件描述符是不合法的
    //会导致sendmsg和recvmsg数显异常
    struct iovec vec[1];
    int flag = 1;
    if(*net_fd == -1){
        //正文设置-1，让对端受到
        flag = -1;
        *net_fd = 1;
    }
    vec[0].iov_base = &flag;
    vec[0].iov_len = sizeof(int);

    hdr.msg_iov = vec;
    hdr.msg_iovlen = 1;

    struct cmsghdr *pcmsg = (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;

    void *addr = CMSG_DATA(pcmsg);
    int *p_int = (int *)addr;
    *p_int = *net_fd;

    hdr.msg_control = pcmsg;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));

    int ret = sendmsg(socket_local_fd, &hdr, 0);
    ERROR_CHECK(ret, -1, "write_net_fd sendmsg\n");

    return 0;
}

//根据客户端连接文件对象和客户端通信
int netToClient(int netfd){
    char buf[1024];
    memset(buf, 0, 1024);
    int ret = recv(netfd, buf, 1024, 0);
    if(ret == 0){
        printf("client has disconneted, fd: %d\n", netfd);
        return -1;
    }
    printf("client: %s", buf);
    const char *str = "hello\n";
    send(netfd, str, strlen(str), 0);
    //子线程睡眠，测试让其他线程处理
    sleep(10);
    return 0;
}
