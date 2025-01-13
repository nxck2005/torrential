#include "uihandler.hpp"
#include "uidefines.hpp"
#include <string>
#include <stdlib.h>
#include <signal.h>

struct terminfo term;

void drawTitle() {
    getmaxyx(stdscr, term.yMax, term.xMax);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    WINDOW* titlewin = newwin(2, term.xMax - 1, 1, 1);
    wattron(titlewin, COLOR_PAIR(1));
    box(titlewin, 0, 0);
    refresh();
    wrefresh(titlewin);
    attroff(COLOR_PAIR(1));
    wattroff(titlewin, COLOR_PAIR(1));
    mvwprintw(titlewin, 0, 2, "torrential 0.0.0.1 alpha");
    refresh();
    wrefresh(titlewin);
    getch();
}

void drawMenu() {
    getmaxyx(stdscr, term.yMax, term.xMax);
}

void drawAllWindows() {
    drawTitle();
}

void handleResize(int sig) {
    endwin();
    refresh();
    getmaxyx(stdscr, term.yMax, term.xMax);
    clear();
    drawAllWindows();
}

void startncurses(bool cBreakTrue, bool noEchoTrue) {
    initscr();
    if(cBreakTrue) {
        cbreak();
    }
    if(noEchoTrue) {
        noecho();
    }
    if(!has_colors() && !can_change_color()) {
        printw("Terminal doesn't support colors or changing colors. Exiting!");
        getch();
        exit(1);
    }
    curs_set(0);
    start_color();
    signal(SIGWINCH, handleResize);
}

void endncurses() {
    curs_set(1);
    endwin();
}