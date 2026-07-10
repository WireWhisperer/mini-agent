#ifndef _MAIN_H_
#define _MAIN_H_

#include <ncurses.h>
#include <time.h>
#include<unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

#include "app.h"
#include "command.h"
#include "input.h"
#include "markdown.h"
#include "tui.h"

void Get_CtrlC_handler(int sig); //捕捉Ctrl-C信号

#endif