#include <ncurses.h>
using namespace std;

int main(int argc, char ** argv) {
    // initialises screen
    // sets up memory and clears the screen
    initscr();
    raw();
    noecho();

    int x, y;
    
    x = y = 10;

    // Move cursor to 0,0 (y, x)
    move(y, x);

    // Prints a string (const char *) to a window
    printw("torrential 0.0.0.1");

    // Refresh the screen to match what's in memory
    refresh();

    // Wait for us to press a key
    int c = getch();

    // clears the screen
    clear();

    mvprintw(0, 0, "%c", c);

    getch();

    // Deallocates memory and ends ncurses
    endwin();
    return 0;
}
