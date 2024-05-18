#include <my_header.h>

int main(int argc,char *argv[])
{
    char *sourceIP = "192.168.233.129";
    char *sourcePort = "5050";
    int socketFd = socket(AF_INET , SOCK_STREAM , 0);
    struct sockaddr_in socketAddr;
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port =htons(atoi(sourcePort));
    socketAddr.sin_addr.s_addr = inet_addr(sourceIP);
    connect(socketFd,(struct sockaddr *)&socketAddr,sizeof(socketAddr));    

    int epollfd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    struct epoll_event event_socket;
    event.events = EPOLLIN;
    event.data.fd = socketFd;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,socketFd,&event_socket);

    int tag = -1 ;
    while(1)
    {
        struct epoll_event list[5];
        int num = epoll_wait(epollfd,list,5,-1);
        for(int i = 0 ;i<num;i++)
        {
            struct epoll_event event = list[i];
            if(event.data.fd == STDIN_FILENO){
                char buf[60]={0};
                int res_read = read(STDIN_FILENO,buf,sizeof(buf));
                if(res_read == 0)
                {   
                    printf("tuichu\n");
                    break;
                }
                send(socketFd,buf,strlen(buf),0);

            }else if (event.data.fd == socketFd)
            {
                char buf2[60]={0};
                int res_recv = recv(socketFd,buf2,sizeof(buf2),0);
                if(res_recv == 0){
                    printf("对方结束\n");
                    tag = 0;
                    break;
                }
                printf("%s",buf2);
                /* write(STDOUT_FILENO,buf2,sizeof(buf2)); */

            }
        }

        if(tag != -1){
            break;
        }
    }
    close(socketFd);
    return 0;
}

