#include "main.h"

WINDOW *win_commu_box;
WINDOW *win_commu_data;
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
    time_t rawtime;  //记录当前时间
    
    init_tui(row, col);

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
        wprintw(win_commu_data, "user: \n%s\n\n", buffer);
        wrefresh(win_commu_data);
        //处理输入内容
        react_to_input(buffer);
        clear_Win_Input(win_input);
    }

    destroy_win(win_commu_box);
    destroy_win(win_commu_data);
    destroy_win(win_state);
    destroy_win(win_input);

    endwin();           
    return 0;
}

void Get_CtrlC_handler(int sig) 
{
	signal(sig, SIG_IGN);
    clear_Win_Input(win_input);

}