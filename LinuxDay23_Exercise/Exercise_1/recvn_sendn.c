#include <nofish_header.h>

//发送n个字节
int sendn(int fd, const void * buff, int len);
//接收n个字节
int recvn(int fd, void * buff, int len);

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


int main(int argc, char** argv)
{
    return 0;
}


