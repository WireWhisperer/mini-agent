#include "tui.h"

extern WINDOW *win_commu_box;
extern WINDOW *win_commu_data;
extern WINDOW *win_state;
extern WINDOW *win_input;

void destroy_win(WINDOW *local_win)
{  
    wclear(local_win);
    wrefresh(local_win);
    delwin(local_win);
}

void change_home(char* path)
{
    path = path;
    return;
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
    wrefresh(win_state);
}