#include "uihandler.hpp"
#include "uidefines.hpp"
#include <string>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <iostream>
#include <csignal>

using namespace std;

#define VERSION "0.0.0.2-alpha"

struct terminfo term;
const char* buildTimestamp = __TIMESTAMP__;

// Resize flag, type can be handled easily w a signal handler
volatile sig_atomic_t resize_needed = 0;


void initColors() {
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}


void drawTitle() {
    getmaxyx(stdscr, term.yMax, term.xMax);
    attron(COLOR_PAIR(1));

    // Creates (2 x (xMax-1)) window at 1,1
    WINDOW* titlewin = newwin(2, term.xMax - 1, 1, 1);
    wattron(titlewin, COLOR_PAIR(1));
    box(titlewin, 0, 0);
    refresh();
    wrefresh(titlewin);
    attroff(COLOR_PAIR(1));
    wattroff(titlewin, COLOR_PAIR(1));
    mvwprintw(titlewin, 0, 2, "torrential %s", VERSION);
    mvwprintw(titlewin, 0, term.xMax - 44, "build timestamp: %s", buildTimestamp);
    refresh();
    wrefresh(titlewin);
}

void drawMenu() {
    getmaxyx(stdscr, term.yMax, term.xMax);
    attron(COLOR_PAIR(1));


    // no of rows
    int xDim = term.yMax - 7;

    // no of cols
    int yDim = term.xMax / 5;

    WINDOW* menuwin = newwin(xDim, yDim, 3, 1);
    wattron(menuwin, COLOR_PAIR(1));
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    attroff(COLOR_PAIR(1));
    wattroff(menuwin, COLOR_PAIR(1));

    int textBegin = term.yMax/4;

    mvwprintw(menuwin, textBegin, 2, "> Current");
    mvwprintw(menuwin, textBegin + 2, 2, "> Download");
    mvwprintw(menuwin, textBegin + 4, 2, "> Seeding");
    refresh();
    wrefresh(menuwin);
}

void drawContent() {
    getmaxyx(stdscr, term.yMax, term.xMax);
    attron(COLOR_PAIR(1));

    // no of rows same as menu
    int xDim = term.yMax - 7;

    // reduce the space taken by menu
    int yDim = term.xMax - ((term.xMax / 5) + 2);

    WINDOW* contentwin = newwin(xDim, yDim, 3, (term.xMax / 5) + 2);
    wattron(contentwin, COLOR_PAIR(1));
    box(contentwin, 0, 0);
    refresh();
    wrefresh(contentwin);
    attroff(COLOR_PAIR(1));
    wattroff(contentwin, COLOR_PAIR(1));
}

void drawAllWindows() {
    drawTitle();
    drawMenu();
    drawContent();
}

void handleResize(int sig) {
    resize_needed = 1;
}

void doResize() {

/*
    * Signal Handling Explanation (For myself)
    * --------------------------
    * When the terminal window is resized or font size is changed (Ctrl+scroll),
    * the terminal sends a SIGWINCH (signal window change) to our program.
    * 
    * The signal handling works in three parts:
    * 
    * 1. Signal Detection:
    *    - We use a volatile sig_atomic_t flag (resize_needed) that can be safely
    *      modified in a signal handler
    *    - When SIGWINCH arrives, handleResize() sets this flag to 1
    * 
    * 2. Signal Blocking:
    *    sigemptyset(&mask)               - Creates empty signal mask (like a blank "Do Not Disturb" sign)
    *    sigaddset(&mask, SIGWINCH)       - Adds SIGWINCH to mask (writes "No resizing" on the sign)
    *    sigprocmask(SIG_BLOCK, ...)      - Blocks signals in mask (puts up the sign)
    *    sigprocmask(SIG_SETMASK, ...)    - Restores original mask (takes down the sign)
    * 
    * 3. Main Loop:
    *    - Continuously checks resize_needed flag
    *    - If set, calls doResize() which:
    *      a) Blocks new SIGWINCH signals
    *      b) Updates terminal dimensions
    *      c) Redraws windows
    *      d) Unblocks signals
    * 
    * This prevents crashes by ensuring we don't try to handle multiple resize
    * events simultaneously, especially during rapid resizing (Ctrl+scroll).
*/

    // Block SIGWINCH during resize op
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGWINCH);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);

    resize_needed = 0;

    // Get new terminal size
    getmaxyx(stdscr, term.yMax, term.xMax);

    // Give term time to settle
    struct timespec ts = {0, 50000000};
    nanosleep(&ts, NULL);
    
    // Delete and reinit
    endwin();
    refresh();
    clear();
    drawAllWindows();

    // Restore signal mask
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
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
    initColors();
    signal(SIGWINCH, handleResize);
}

void endncurses() {
    curs_set(1);
    endwin();
}