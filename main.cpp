#include <ncurses.h>
#include <string>
#include <stdlib.h>
using namespace std;

struct terminfo {
    int xMax;
    int yMax;
};
struct terminfo term;

void startncurses(bool cBreakTrue,  bool noEchoTrue) {
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
}

void endncurses() {
    curs_set(1);
    endwin();
}

int main(void) {
    startncurses(true, true);

    /* Initialize terminal details */

    getmaxyx(stdscr, term.yMax, term.xMax);

    WINDOW * titlewin = newwin(2, term.xMax - 1, 1, 1);
    box(titlewin, 0, 0);
    refresh();
    wrefresh(titlewin);

    mvwprintw(titlewin, 0, 2, "torrential 0.0.0.1 alpha");
    refresh();
    wrefresh(titlewin);

    getch();
    endncurses();
}