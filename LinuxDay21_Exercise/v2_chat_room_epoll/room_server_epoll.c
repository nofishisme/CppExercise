#include <nofish_header.h>

struct custumer{
    int alive;
    int netfd;
    time_t time_val;
}custumer;
int main(int argc, char *argv[])
{                                  
    const char *ip = "192.168.48.128";
    const char *port = "8080";

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(port));
    sockaddr.sin_addr.s_addr = inet_addr(ip);

    int reuse = 1;
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    int res = bind(sockFd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    ERROR_CHECK(res, -1, "bind");
    listen(sockFd, 10);

    int epollFd = epoll_create(1);
    struct epoll_event event_read;
    event_read.events = EPOLLIN;
    event_read.data.fd = sockFd;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, sockFd, &event_read); 

    struct custumer list[10];
    memset(list, 0, 10*sizeof(custumer));
    int inet = 0;
    while(1){
        struct epoll_event events[5];
        int num = epoll_wait(epollFd, events, 5, 1);
        for(int i = 0; i < num; i++){
            int eventsFd = events[i].data.fd;
            int connectFd;
            if(eventsFd == sockFd){
                struct epoll_event event_read;
                event_read.events = EPOLLIN;
                connectFd = accept(sockFd, NULL, NULL);
                list[inet].alive = 1;
                list[inet].netfd = connectFd;
                list[inet].time_val = time(NULL);
                inet++;
                event_read.data.fd = connectFd;
                epoll_ctl(epollFd, EPOLL_CTL_ADD, connectFd, &event_read); 
            }
            for(int j = 0; j < inet; j++){
                if(eventsFd == list[j].netfd){
                    char buf[60] = {0};
                    int res = recv(sockFd, buf, sizeof(buf), 0);
                    if(res == 0){
                        printf("--custumer[%d]已断开--\n",j);
                        struct epoll_event event_read;
                        event_read.events = EPOLLIN;
                        event_read.data.fd = list[j].netfd;
                        epoll_ctl(epollFd, EPOLL_CTL_DEL, list[j].netfd, &event_read); 
                        list[j].alive = 0;
                        close(list[j].netfd);
                        continue;
                    }
                    list[j].time_val = time(NULL);
                    ERROR_CHECK(res, -1, "recv");
                    for(int k = 0; k < inet; k++){
                        if(list[k].alive == 1 && j != k){
                            int res = send(list[k].netfd, buf, sizeof(buf), 0); 
                            ERROR_CHECK(res, -1, "send");
                        }
                    }
                }
            }
        }
        for(int i = 0; i < inet; i++){
            int time_new = time(NULL);
            if((list[i].alive == 1) && (list[i].time_val - time_new > 10)){
                printf("--custumer[%d]超时--\n", i);
                struct epoll_event event_read;
                event_read.data.fd = list[i].netfd;
                epoll_ctl(epollFd, EPOLL_CTL_DEL, list[i].netfd, &event_read); 
                list[i].alive = 0;
                close(list[i].alive);

            }
        }
    }
    close(sockFd);
    return 0;
}

