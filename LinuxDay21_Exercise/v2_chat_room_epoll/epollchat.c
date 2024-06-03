#include <nofish_header.h>
typedef  struct conn_s{
    int netfd;
    int isalive;
    time_t lastTime;
}conn_t;

int main(int argc,char *argv[])
{
    char *sourceIP = "192.168.37.128";
    char *sourcePort = "8080";
    int socketFd = socket(AF_INET , SOCK_STREAM , 0);
    struct sockaddr_in socketAddr;
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(atoi(sourcePort));
    socketAddr.sin_addr.s_addr = inet_addr(sourceIP);
    int reuse = 1;
    setsockopt(socketFd,SOL_SOCKET,SO_REUSEPORT,&reuse,sizeof(reuse));
    bind(socketFd,(struct sockaddr *)&socketAddr,sizeof(socketAddr));

    listen(socketFd,10);
    int epollfd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = socketFd;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,socketFd,&event);
    conn_t list[1024];
    memset(list ,0 ,1024 * sizeof(conn_t));
    int index = 0;
    while(1)
    {

        struct epoll_event events[10];
        int num = epoll_wait(epollfd,events,10,1000);
        for(int i = 0 ;i < num ; ++i )
        {
            struct epoll_event event = events[i];
            if(event.data.fd == socketFd){
                int netfd = accept(socketFd,NULL,NULL);
                struct epoll_event temp;
                temp.events = EPOLLIN;
                temp.data.fd = netfd;
                epoll_ctl(epollfd,EPOLL_CTL_ADD,netfd,&temp);
                list[index].isalive = 1;
                list[index].netfd = netfd;
                time(&list[index].lastTime);
                index++;
            }else{
                for(int k = 0 ;k<index ;++k)
                {
                    if(list[k].netfd == event.data.fd&&list[k].isalive == 1){
                        time(&list[k].lastTime);
                        break;
                    }
                }
                char buf[60]={0};
                int ret = recv(event.data.fd,buf,sizeof(buf),0);
                if(ret == 0)
                {
                    for(int k = 0; k<index;++k)
                    {
                        if(list[k].netfd == event.data.fd && list[k].isalive==1)
                        {
                            list[k].isalive = 0;
                            break;
                        }
                    }
                    epoll_ctl(epollfd,EPOLL_CTL_DEL,event.data.fd,NULL);
                    close(event.data.fd);
                    continue;
                }
                for(int j = 0; j<index;++j)
                {
                    printf("1\n");
                    if(list[j].isalive ==1 && list[j].netfd != event.data.fd)
                    {
                        printf("2,%s\n",buf);
                        int send_ret = send(list[j].netfd,buf,sizeof(buf),0);
                        ERROR_CHECK(send_ret,-1,"send error");
                    }
                    printf("3\n");
                }
            }
        }
        time_t now_t;
        time(&now_t);
        for(int i = 0 ;i<index ;++i)
        {
            if(list[i].isalive==1 && now_t-list[i].lastTime>10)
            {
                list[i].isalive = 0;
                epoll_ctl(epollfd,EPOLL_CTL_DEL,list[i].netfd,NULL);
                close(list[i].netfd);
            }
        }
    }
    close(socketFd);
    return 0;
}

