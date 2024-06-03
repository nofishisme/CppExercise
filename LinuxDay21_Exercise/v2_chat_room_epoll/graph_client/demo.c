#include <nofish_header.h>

#define Y_START_LINES 3
int main()
{
    initscr();
    char title[256] = " Welcome to Nofish's Private Chat Room ";
    //10个*
    char fringe[64] = "*@*@*@*@*@*";
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

    //创建epoll对象
    int epoll_fd = epoll_create(1);
    ERROR_CHECK(epoll_fd, -1, "epoll_create\n");
    //创建epoll监听事件，监听标准输入和连接方的文件描述符
    struct epoll_event stdin_event;
    memset(&stdin_event, 0, sizeof(stdin_event));
    stdin_event.events = EPOLLIN;
    stdin_event.data.fd = STDIN_FILENO ;
    //将epoll事件加入监听集合
    int res_ctl1 = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 
                             STDIN_FILENO, &stdin_event);
    ERROR_CHECK(res_ctl1, -1, "epoll_ctl1\n");
    
    while(1) {
         //接受监听就绪事件集合的数组
         struct epoll_event event_set[2];
         //监听就绪
         int ready = epoll_wait(epoll_fd, event_set, 2, -1);
         if(ready == -1){
         }else if(ready == 0){
         } else {
             char buff[1024];
             memset(buff, 0, 1024);
             sprintf(buff, "client: ");
             //输入要发送的消息
             wgetnstr(input2_window, buff + strlen(buff), 1024);
             strcat(buff, "\n");

             //发送给消息显示窗口
             wprintw(error_window, "%s", buff);
             wrefresh(error_window);
             //刷新，光标移动回输入窗口
             werase(input2_window);
             wrefresh(input2_window);
             if(buff[0] == 'q') {
                 break;
             }
         }
    }


    endwin();
    return 0;
}

