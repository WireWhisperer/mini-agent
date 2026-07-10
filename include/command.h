#ifndef COMMAND_H
#define COMMAND_H

#include <ncurses.h>
#include <time.h>
#include<unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include "tui.h"

void react_to_input(char* buffer); //处理输入内容
void commond_Read(char* ptr); //处理读取命令
#endif