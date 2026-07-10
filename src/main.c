
#include <ncurses.h>
#include <time.h>
#include<unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

void destroy_win(WINDOW *local_win);
void change_home(char* path); //将读取地址的home替换成~
void Get_CtrlC_handler(int sig); //捕捉Ctrl-C信号
void clear_Win_Input(WINDOW *win_input); //清空输入窗口
void time_Update(time_t *rawtime, int col); //更新时间
void react_to_input(char* buffer, int *Win_Commu_Pos); //处理输入内容

WINDOW *win_commu;
WINDOW *win_state;
WINDOW *win_input;

int main(void)
{
    initscr();
    start_color();
    
    int row,col;    //保存当前主窗口大小
    int curse_row,curse_col; //保存当前光标位置
    char cwd[1024]; //记录当前地址
    char buffer[1024]; //记录输入缓冲区
    int Win_Commu_Pos = 1; //记录通信窗口的对话位置
    time_t rawtime;  //记录当前时间
    getmaxyx(stdscr, row, col);
    
    //创建三个子窗口
    win_commu = subwin(stdscr, row - 8, col, 0, 0);
    win_state = subwin(stdscr, 3, col, row-8, 0);
    win_input = subwin(stdscr, 5, col, row-5, 0);
    //画框框
    box(win_commu, '|', '-');
    box(win_state, '|', '-');
    box(win_input, '|', '-');
    
    scrollok(win_commu, true);        // 在 WIN 指针指向的窗口中开启 (true)/关闭 (false) 滚屏
    wsetscrreg(win_commu, 1, getmaxy(win_commu) - 2);      // 在 scrollok 开启后，可以在窗口中设立一个滚屏区，在该区域内有滚屏
                                 // 滚屏区从第 [x] 行开始，共占 [line] 行

    //显示当前路径和时间
    wmove(win_state, 1, 1);
    getcwd(cwd, sizeof(cwd));
    change_home(cwd);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // [黑]底[白]字
    wattron(win_state, COLOR_PAIR(1));                 
    wprintw(win_state, "%s", cwd);
    wattroff(win_state, COLOR_PAIR(1));                  // 关闭颜色设置，恢复默认


    time_Update(&rawtime, col);

    touchwin(win_state);  

    //光标移动到输入窗口
    clear_Win_Input(win_input);

    signal(SIGINT, Get_CtrlC_handler);

    while(1)
    {
        time_Update(&rawtime, col); //更新时间
        wscanw(win_input, "%s", buffer);

        //打印输入内容
        wmove(win_commu, curse_row, curse_col+1);
        wprintw(win_commu, "user: %s", buffer);
        wrefresh(win_commu);
        //处理输入内容
        react_to_input(buffer, &Win_Commu_Pos);
        clear_Win_Input(win_input);
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

void Get_CtrlC_handler(int sig) 
{
	signal(sig, SIG_IGN);
    clear_Win_Input(win_input);

}

void clear_Win_Input(WINDOW *win_input)
{
    wclear(win_input);
    box(win_input, '|', '-');
    wmove(win_input, 1, 1);
    wprintw(win_input, ">");
    wmove(win_input, 1, 2);
    refresh();
}

void time_Update(time_t *rawtime, int col)
{
    time( rawtime );
    struct tm *info = localtime( rawtime );
    wmove(win_state, 1, col-10);
    wprintw(win_state, "%d:%d:%d", info->tm_hour, info->tm_min, info->tm_sec);
}

void react_to_input(char* buffer, int *Win_Commu_Pos)
{
    if (!strcmp(buffer, "/exit")) 
    {
        destroy_win(win_commu);
        destroy_win(win_state);
        destroy_win(win_input);
        endwin();
        exit(0);
    }
    else
    {
        //wmove(win_commu, *Win_Commu_Pos, 1);
        wprintw(win_commu, "Assistant:\n ## `429` Too many Requests\n\n**The server is busy, please try again later.**\n\n");
        wrefresh(win_commu);
    }
}