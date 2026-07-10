#ifndef MARKDOWN_H
#define MARKDOWN_H

#include <ncurses.h>
#include <time.h>
#include<unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

void render_markdown(WINDOW *win, const char *markdown); // 渲染 Markdown 内容到指定窗口

#endif