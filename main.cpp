#include <ncurses.h>
#include <string>
#include <stdlib.h>
#include <signal.h>
using namespace std;

/* Structure to hold terminal information, including maximum dimensions. */
struct terminfo {
    int xMax; /* Maximum number of columns */
    int yMax; /* Maximum number of rows */
};

struct terminfo term; /* Global instance of terminal info */

/* Function to draw the title window */
void drawTitle() {
    /* Update terminal size */
    getmaxyx(stdscr, term.yMax, term.xMax);

    /* Initialize color pair for the title */
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    /* Create a new window for the title */
    WINDOW * titlewin = newwin(2, term.xMax - 1, 1, 1);
    wattron(titlewin, COLOR_PAIR(1)); /* Turn on color pair for the window */

    /* Draw a box around the title window */
    box(titlewin, 0, 0);
    refresh();
    wrefresh(titlewin);

    /* Turn off the color attributes */
    attroff(COLOR_PAIR(1));
    wattroff(titlewin, COLOR_PAIR(1));

    /* Print the title text inside the title window */
    mvwprintw(titlewin, 0, 2, "torrential 0.0.0.1 alpha");
    refresh();
    wrefresh(titlewin);

    /* Wait for a key press before continuing */
    getch();
}

/* Function to redraw all windows (currently only the title window) */
void drawAllWindows() {
    drawTitle();
}

/* Signal handler for window resize (SIGWINCH signal) */
void handleResize(int sig) {
    /* Suspend curses session to handle resize gracefully */
    endwin(); /* End the ncurses window */
    refresh(); /* Refresh the ncurses session */
    getmaxyx(stdscr, term.yMax, term.xMax); /* Update terminal size */
    clear(); /* Clear the screen */
    drawAllWindows(); /* Redraw all windows after resize */
}

/* Function to initialize the ncurses environment */
void startncurses(bool cBreakTrue, bool noEchoTrue) {
    initscr(); /* Start ncurses mode */

    /* Set terminal mode based on parameters */
    if(cBreakTrue) {
        cbreak(); /* Disable line buffering */
    }
    if(noEchoTrue) {
        noecho(); /* Disable echoing of typed characters */
    }

    /* Check for color support */
    if(!has_colors() && !can_change_color()) {
        printw("Terminal doesn't support colors or changing colors. Exiting!");
        getch(); /* Wait for user input before exiting */
        exit(1);
    }

    curs_set(0); /* Hide the cursor */
    start_color(); /* Enable color functionality */
    signal(SIGWINCH, handleResize); /* Attach signal handler for window resize */
}

/* Function to clean up and end the ncurses session */
void endncurses() {
    curs_set(1); /* Restore the cursor */
    endwin(); /* End ncurses mode */
}


/* Main function */
int main(void) {
    startncurses(true, true); /* Initialize ncurses with cbreak and noecho mode */
    drawAllWindows(); /* Draw all windows */
    endncurses(); /* End ncurses session */
}
