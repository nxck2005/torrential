#include "ui/uidefines.hpp"
#include "ui/uihandler.hpp"
using namespace std;

/* main */

int main(void) {
    startncurses(true, true); /* Initialize ncurses with cbreak and noecho mode */
    drawAllWindows(); /* Draw all windows */
    endncurses(); /* End ncurses session */
    return 0;
}
