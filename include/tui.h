#ifndef TUI_H
#define TUI_H

#include "main.h"

void destroy_win(WINDOW *local_win);  //销毁窗口
void change_home(char* path); //将读取地址的home替换成~
void clear_Win_Input(WINDOW *win_input); //清空输入窗口
void time_Update(time_t *rawtime, int col); //更新时间

#endif

