#pragma once
#ifndef __WY_processpool_HPP__
#define __WY_processpool_HPP__

typedef enum {
    FREE,
    BUSY
}status_t;

typedef struct worker_status_t {
    int _pid; //进程id
    status_t _status;//进程状态：忙或空闲
    int socket_local_fd;//socket本地通信的文件描述符：用于main和子进程通信
} worker_process_t;

//初始化进程池
int initprocesspool(worker_process_t *p, int num);


//处理连接，监听到的连接交个空闲的线程
int toProcessPoolDealNet(int net_fd, worker_process_t *p, int num);


//启动一个工作进程
int startWorker(int socket_local_fd);

//工作进程，从本地socket中读取main进程发过来的客户端连接对象
int read_net_fd(int socket_local_fd, int *netfd);

//main进程accept获得的客户端连接对象发给工作进程
int write_net_fd(int socket_local_fd, int *net_fd);

//根据客户端连接文件对象和客户端通信
int netToClient(int netfd);
#endif

