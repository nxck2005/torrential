// header files
#include <ncurses.h>
#include "ui/uihandler.hpp"
/* #include "torrent/bencode.cpp" */
/* main */

extern volatile sig_atomic_t resize_needed;
void doResize();

// Main loop for program here

int main(void) {
    // Initialize everything
    startncurses(true, true);
    drawAllWindows();

    while (1) {
        // Check for resize first
        if (resize_needed != 0) {
            doResize();
        }
        
        // Wait up to 100ms for input, and so that doResize() doesn't block getch()
        timeout(100);
        int ch = getch();
        
        // Handle input if we got any
        if (ch != ERR) {
            switch (ch) {
                case 'q':
                    goto cleanup; 
            }
        }
        
        // Could add other periodic tasks here
        // Like updating display, checking status, etc.
    }

cleanup:
    endncurses();
    return 0;
}
