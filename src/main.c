
#include <ncurses.h>
#include <time.h>
#include<unistd.h>
#include <string.h>

void destroy_win(WINDOW *local_win);
void change_home(char* path); //将读取地址的home替换成~

int main(int argc, char *argv[])
{
    initscr();
    start_color();
    
    int row,col;    //保存当前主窗口大小
    char cwd[1024]; //记录当前地址
    char buffer[1024]; //记录输入缓冲区
    time_t rawtime;  //记录当前时间
    struct tm *info; //解析当前时间
    getmaxyx(stdscr, row, col);
    
    //创建三个子窗口
    WINDOW *win_commu = subwin(stdscr, row - 8, col, 0, 0);
    WINDOW *win_state = subwin(stdscr, 3, col, row-8, 0);
    WINDOW *win_input = subwin(stdscr, 5, col, row-5, 0);
    //画框框
    box(win_commu, '|', '-');
    box(win_state, '|', '-');
    box(win_input, '|', '-');
    

    //显示当前路径和时间
    wmove(win_state, 1, 1);
    getcwd(cwd, sizeof(cwd));
    change_home(cwd);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // [黑]底[白]字
    wattron(win_state, COLOR_PAIR(1));                 
    wprintw(win_state, "%s", cwd);
    wattroff(win_state, COLOR_PAIR(1));                  // 关闭颜色设置，恢复默认


    time( &rawtime );
    info = localtime( &rawtime );
    wmove(win_state, 1, col-10);
    wprintw(win_state, "%d:%d:%d", info->tm_hour, info->tm_min, info->tm_sec);

    touchwin(win_state);  
    //光标移动到输入窗口
    wmove(win_input, 1, 1);
    wprintw(win_input, ">");
    wmove(win_input, 1, 2);
    refresh();


    while(1)
    {
        wscanw(win_input, "%s", buffer);
        wclear(win_input);
        box(win_input, '|', '-');
        wmove(win_input, 1, 1);
        wprintw(win_input, ">");
        wmove(win_input, 1, 2);
        refresh();
    }
    



    destroy_win(win_commu);
    destroy_win(win_state);
    destroy_win(win_input);

    endwin();           
    return 0;
}

void destroy_win(WINDOW *local_win)
{   
    /* box(local_win, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners 
     * and so an ugly remnant of window. 
     */
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}

void change_home(char* path)
{
    int a = 1;
}