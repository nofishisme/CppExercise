#pragma once
#ifndef __WY_tcpConnection_HPP__
#define __WY_tcpConnection_HPP__


//初始化服务端套接字监听
int initTcpSocket(int *socket_fd, const char *ip, const char *port);

//添加监听
int epoll_addfd(int epoll_fd, int file_fd);
//删除监听
int epoll_addfd(int epoll_fd, int file_fd);

//处理新连接
int handle_new_connection(int epoll_fd, int socket_fd);

//处理客户端发来的请求
int handle_message(int connect_fd);

//发送n个字符，配合非阻塞使用
int sendn(int fd, const void * buff, int len);
//接受n个字符，配合非阻塞使用
int recvn(int fd, void * buff, int len);

#endif

