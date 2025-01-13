#pragma once

#include <ncurses.h>

// All your function declarations
void drawTitle();
void drawMenu();
void drawAllWindows();
void handleResize(int sig);
void startncurses(bool cBreakTrue, bool noEchoTrue);
void endncurses();