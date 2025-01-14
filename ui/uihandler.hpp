#pragma once

#include <ncurses.h>
#include <csignal>

extern volatile sig_atomic_t resize_needed;

// All your function declarations
void drawTitle();
void drawMenu();
void drawContent();
void drawAllWindows();
void handleResize(int sig);
void doResize();
void startncurses(bool cBreakTrue, bool noEchoTrue);
void endncurses();