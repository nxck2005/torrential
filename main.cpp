#include "ui/uidefines.hpp"
#include "ui/uihandler.hpp"
using namespace std;

/* main */

int main(void) {
    // Initialize everything
    startncurses(true, true);
    drawAllWindows();

    while (1) {
        // Check for resize first
        if (resize_needed) {
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