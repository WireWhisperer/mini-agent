#include "app.h"

extern WINDOW *win_commu_box;
extern WINDOW *win_commu_data;
extern WINDOW *win_state;
extern WINDOW *win_input;

void init_tui(int row, int col)
{
    getmaxyx(stdscr, row, col);
    
    //创建三个子窗口
    win_commu_box = subwin(stdscr, row - 8, col, 0, 0);
    win_commu_data = subwin(stdscr, row - 10, col-2, 1, 1);
    win_state = subwin(stdscr, 3, col, row-8, 0);
    win_input = subwin(stdscr, 5, col, row-5, 0);
    //画框框
    box(win_commu_box, '|', '-');
    box(win_state, '|', '-');
    box(win_input, '|', '-');
    
    scrollok(win_commu_data, true);        // 在 WIN 指针指向的窗口中开启 (true)/关闭 (false) 滚屏
    wsetscrreg(win_commu_data, 0, getmaxy(win_commu_data));      // 在 scrollok 开启后，可以在窗口中设立一个滚屏区，在该区域内有滚屏
                                 // 滚屏区从第 [x] 行开始，共占 [line] 行
}
    
   