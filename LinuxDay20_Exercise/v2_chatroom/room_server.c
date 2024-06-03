#include <nofish_header.h>

struct custumer{
    int alive;
    int netfd;
}custumer;
int main(int argc, char *argv[])
{                                  
    const char *ip = "192.168.37.128";
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
    listen(sockFd, 100);

    fd_set set_base;
    FD_ZERO(&set_base);
    FD_SET(sockFd, &set_base);
    struct custumer list[10];
    memset(list, 0, 10 * sizeof(custumer));
    while(1){
        fd_set set_while;
        memcpy(&set_while, &set_base, sizeof(set_base));
        select(20, &set_while, NULL, NULL, NULL);
        if(FD_ISSET(sockFd, &set_while)){
            int connectFd = accept(sockFd, NULL, NULL);
            for(int i = 0; i < 10; i++){
                if(list[i].alive == 0){
                    list[i].alive = 1;
                    list[i].netfd = connectFd;
                    FD_SET(connectFd, &set_base);
                    break;
                }
            }
        }
        for(int i = 0; i < 10; i++){
            if(FD_ISSET(list[i].netfd, &set_while)){
                char buf[60] = {0};
                res = recv(list[i].netfd, buf, sizeof(buf), 0);
                ERROR_CHECK(res, -1, "recv");
                if(res == 0){
                    printf("--list[%d]已断开连接--\n", i);
                    FD_CLR(list[i].netfd, &set_base);
                    list[i].alive = 0;
                }
                for(int j = 0; j < 10; j++){
                    if(list[j].alive == 1 && i != j){
                        res = send(list[j].netfd, buf, sizeof(buf), 0);
                        ERROR_CHECK(res, -1, "send");
                    }    
                }
            }
        }
    }
    close(sockFd);
    return 0;
}

