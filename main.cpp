#include <ncurses.h>
using namespace std;

int main(int argc, char ** argv) {
    // initialises screen
    // sets up memory and clears the screen
    initscr();

    // Prints a string (const char *) to a window
    printw("torrential 0.0.0.1");

    // Refresh the screen to match what's in memory
    refresh();

    // Wait for us to press a key
    getch();

    // Deallocates memory and ends ncurses
    endwin();
    return 0;
}