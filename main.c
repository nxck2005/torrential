/* utility to decode a bencode or whatever */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>

int main() {
    initscr();           // Start ncurses mode
    printw("torrential 0.0.0.1"); // Print to screen
    refresh();           // Refresh screen to show output
    getch();            // Wait for user input
    endwin();           // End ncurses mode
    return 0;
}