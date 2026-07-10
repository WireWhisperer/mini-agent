
#include <ncurses.h>

void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{
    initscr();
    cbreak();
    
    int row,col;
    getmaxyx(stdscr, row, col);

    WINDOW *win_commu = subwin(stdscr, row - 8, col, 0, 0);
    WINDOW *win_state = subwin(stdscr, 3, col, row-8, 0);
    WINDOW *win_input = subwin(stdscr, 5, col, row-5, 0);

    box(win_commu, '|', '-');
    box(win_state, '|', '-');
    box(win_input, '|', '-');
    touchwin(stdscr);

    mvwprintw(stdscr, 1, 1, "%d", row);
    mvwprintw(stdscr, 2, 1, "%d", col);

    wmove(win_input, 1, 1);
    refresh();

    int a;
    wscanw(win_input, "%d", &a);

    getch();

    while(1);

    destroy_win(win_commu);
    destroy_win(win_state);
    destroy_win(win_input);

    endwin();           /* End curses mode        */
    return 0;
}

void destroy_win(WINDOW *local_win)
{   
    /* box(local_win, ' ', ' '); : This won't produce the desired
     * result of erasing the window. It will leave it's four corners 
     * and so an ugly remnant of window. 
     */
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    /* The parameters taken are 
     * 1. win: the window on which to operate
     * 2. ls: character to be used for the left side of the window 
     * 3. rs: character to be used for the right side of the window 
     * 4. ts: character to be used for the top side of the window 
     * 5. bs: character to be used for the bottom side of the window 
     * 6. tl: character to be used for the top left corner of the window 
     * 7. tr: character to be used for the top right corner of the window 
     * 8. bl: character to be used for the bottom left corner of the window 
     * 9. br: character to be used for the bottom right corner of the window
     */
    wrefresh(local_win);
    delwin(local_win);
}
