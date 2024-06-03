#include <nofish_header.h>
#include <locale.h>

#define Y_START_LINES 3

//发送n个字符
int sendn(int fd, const void * buff, int len);
//接受n个字符
int recvn(int fd, void * buff, int len);

int main(int argc, char** argv)
{
    // 设置使用系统的默认字符编码  
    setlocale(LC_ALL, "");
    /* 初始化绘制客户端窗口 */
    initscr();
    char title[256] = " Welcome to Nofish's Private Chat Room ";
    //10个*
    char fringe[64] = "**********";
    int screen_height, screen_width;
    getmaxyx(stdscr, screen_height, screen_width);
    int title_len = strlen(title);
    int fringe_len = strlen(fringe);
    //col_pos表示标题的列输出位置
    //line_pos表示标题的行输出位置
    int col_pos = (screen_width - title_len - fringe_len * 2) / 2;
    int line_pos = Y_START_LINES;
    mvprintw(line_pos, col_pos, "%s", fringe);
    attron(A_REVERSE); // 设置反转颜色属性
    mvprintw(line_pos, col_pos + fringe_len, "%s", title);
    attroff(A_REVERSE); // 取消反转颜色属性
    mvprintw(line_pos, col_pos + fringe_len + title_len, "%s", fringe);
    refresh();
    //现在光标在y = screen_height / 2

    /* 聊天记录显示窗口开始绘制 */
    int sub_chat_height = screen_height - Y_START_LINES - 2 - 10;
    int sub_chat_width = screen_width - 10;
    int sub_chat_start_line = Y_START_LINES + 2;
    int sub_chat_start_col = 5;
    //绘制显示子窗口，用于显示聊天
    WINDOW *chat_window = subwin(stdscr, 
                                 sub_chat_height, sub_chat_width, 
                                 sub_chat_start_line, sub_chat_start_col);
    //聊天窗口边框
    box(chat_window, ACS_VLINE, ACS_HLINE);
    wrefresh(chat_window);
    //真正显示聊天记录的窗口
    int sub_chat2_height = sub_chat_height - 2;
    int sub_chat2_width = sub_chat_width - 2;
    int sub_chat2_start_line = sub_chat_start_line + 1;
    int sub_chat2_start_col = sub_chat_start_col + 1;

    WINDOW *chat2_window = subwin(stdscr,
                                  sub_chat2_height, sub_chat2_width,
                                  sub_chat2_start_line, sub_chat2_start_col);
    wrefresh(chat2_window);
    //允许消息记录窗口卷屏
    scrollok(chat2_window, true);

    /* 聊天记录显示窗口绘制结束 */
    
    /* 聊天消息输入边框绘制开始 */
    //绘制子窗口，用于输入聊天信息
    int sub_input_height = 5;
    int sub_input_width = sub_chat_width;
    int sub_input_start_line = sub_chat_start_line + sub_chat_height;
    int sub_input_start_col = sub_chat_start_col;

    WINDOW *input_window = subwin(stdscr,
                                  sub_input_height, sub_input_width,
                                  sub_input_start_line, sub_input_start_col);
    //绘制输入聊天消息子窗口边框
    box(input_window, ACS_VLINE, ACS_HLINE);
    wrefresh(input_window);
    //真正用于输入的子窗口
    int sub_input2_height = sub_input_height - 2;
    int sub_input2_width = sub_input_width - 2;
    int sub_input2_start_line = sub_input_start_line + 1;
    int sub_input2_start_col = sub_input_start_col + 1;

    WINDOW *input2_window = subwin(stdscr,
                                  sub_input2_height, sub_input2_width,
                                  sub_input2_start_line, sub_input2_start_col);
    wrefresh(input2_window);
    //允许输入窗口卷屏
    scrollok(input2_window, true);

    //客户端报错位置
    int sub_error_height = 3;
    int sub_error_width = sub_input_width;
    int sub_error_start_line = sub_input_start_line + sub_input_height + 2;
    int sub_error_start_col = sub_input_start_col;

    WINDOW *error_window = subwin(stdscr, 
                                  sub_error_height, sub_error_width,
                                  sub_error_start_line, sub_error_start_col);

    wrefresh(error_window);
    //允许错误窗口卷屏
    scrollok(error_window, true);
    //初始化完成时光标应该在消息输入窗口
    touchwin(input2_window);
    wrefresh(input2_window);
    /* 聊天消息输入窗口绘制结束 */
    /* 窗口绘制结束 */

    //以下是客户端初始化
    const char *sourceIP = "192.168.37.130";
    const char *sourcePort = "8080";

    //获取套接字
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if( socket_fd == -1 ) {
        wprintw(error_window, "error: socket\n");
        wrefresh(error_window);
        sleep(5);
        delwin(chat_window);
        delwin(chat2_window);
        delwin(input_window);
        delwin(input2_window);
        delwin(error_window);
        endwin();
        exit(1);
    }

    //构建struct sockaddr类型
    struct sockaddr_in client_socket_addr;
    memset(&client_socket_addr, 0, sizeof(client_socket_addr));
    //选择ipv4协议族
    client_socket_addr.sin_family = AF_INET;
    //ip点分十进制转换为网络字节序
    client_socket_addr.sin_addr.s_addr = inet_addr(sourceIP);
    //端口号转换为网络字节序的大端模式
    client_socket_addr.sin_port = htons(atoi(sourcePort));

    //客户端向服务器发起连接请求
    int res_connect = connect(socket_fd, 
                              (struct sockaddr *)&client_socket_addr,
                              sizeof(client_socket_addr));
    if( res_connect == -1 ) {
        wprintw(error_window, "error: connect\n");
        wrefresh(error_window);
        sleep(5);
        delwin(chat_window);
        delwin(chat2_window);
        delwin(input_window);
        delwin(input2_window);
        delwin(error_window);
        endwin();
        exit(1);
    }
    //获取客户端自己的端口和ip
    struct sockaddr_in localaddr;
    socklen_t len = sizeof(localaddr);
    getsockname(socket_fd,
    (struct sockaddr *)&localaddr, &len);
    char local_ip[16];
    strcpy(local_ip, inet_ntoa(localaddr.sin_addr));
    int  local_port = ntohs(localaddr.sin_port);

    //创建epoll对象
    int epoll_fd = epoll_create(1);
    if( epoll_fd == -1 ) {
        wprintw(error_window, "error: epoll_create\n");
        wrefresh(error_window);
        sleep(5);
        delwin(chat_window);
        delwin(chat2_window);
        delwin(input_window);
        delwin(input2_window);
        delwin(error_window);
        endwin();
        exit(1);
    }
    //创建epoll监听事件，监听标准输入和连接方的文件描述符
    struct epoll_event stdin_event, read_event;
    memset(&stdin_event, 0, sizeof(stdin_event));
    memset(&read_event, 0, sizeof(read_event));
    stdin_event.events = EPOLLIN;
    stdin_event.data.fd = STDIN_FILENO ;
    read_event.events = EPOLLIN;
    read_event.data.fd = socket_fd;
    //将epoll事件加入监听集合
    int res_ctl1 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &stdin_event);
    if( res_ctl1 == -1 ) {
        wprintw(error_window, "error: epoll_ctl\n");
        wrefresh(error_window);
        sleep(5);
        delwin(chat_window);
        delwin(chat2_window);
        delwin(input_window);
        delwin(input2_window);
        delwin(error_window);
        endwin();
        exit(1);
    }
    int res_ctl2 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &read_event);
    if( res_ctl2 == -1 ) {
        wprintw(error_window, "error: epoll_ctl\n");
        wrefresh(error_window);
        sleep(5);
        delwin(chat_window);
        delwin(chat2_window);
        delwin(input_window);
        delwin(input2_window);
        delwin(error_window);
        endwin();
        exit(1);
    }

    while(1){
        //接受监听就绪事件集合的数组
        struct epoll_event event_set[2];
        //监听就绪
        int ready = epoll_wait(epoll_fd, event_set, 2, -1);
        if(ready == -1){
            wprintw(error_window, "error: epoll_wait\n");
            wrefresh(error_window);
            touchwin(input2_window);
            wrefresh(input2_window);
        }else if(ready == 0){
            wprintw(error_window, "error: waiting information......\n");
            wrefresh(error_window);
            touchwin(input2_window);
            wrefresh(input2_window);
        }else{
            for(int i = 0; i < ready; ++i){
                int reayd_fd = event_set[i].data.fd;
                if(reayd_fd == STDIN_FILENO) {
                    //处理标准输入
                    char buf[1024];
                    memset(buf, 0, 1024);
                    sprintf(buf, "client(%s:%d): ", local_ip, local_port);
                    //输入要发送的消息
                    wgetnstr(input2_window, buf + strlen(buf), 1024);
                    strcat(buf, "\n");

                    //发送给消息显示窗口
                    wprintw(chat2_window, "%s", buf);
                    wrefresh(chat2_window);
                    //刷新，光标移动回输入窗口
                    werase(input2_window);
                    wrefresh(input2_window);
                    //发送消息到服务器
                    send(socket_fd, buf, strlen(buf), 0);
                }//if STDIN_FILENO
                if(reayd_fd == socket_fd) {
                    char buf[1024];
                    memset(buf, 0, 1024);
                    int read_count = recv(socket_fd, buf, 1024, 0);
                    if(read_count == 0) {
                        wprintw(error_window, "error: server disconnect\n");
                        wprintw(error_window, "error: exit......\n");
                        wrefresh(error_window);
                        touchwin(input2_window);
                        wrefresh(input2_window);
                        sleep(5);
                        delwin(chat_window);
                        delwin(chat2_window);
                        delwin(input_window);
                        delwin(input2_window);
                        delwin(error_window);
                        endwin();
                        exit(1);
                    }
                    //发送消息到消息显示窗口
                    wprintw(chat2_window, "%s", buf);
                    wrefresh(chat2_window);
                    //刷新，光标移动回消息输入窗口
                    werase(input2_window);
                    wrefresh(input2_window);
                }//if STDIN_FILENO
            }
        }
    }
    close(socket_fd);

    delwin(chat_window);
    delwin(chat2_window);
    delwin(input_window);
    delwin(input2_window);
    delwin(error_window);
    endwin();
    return 0;
}

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
