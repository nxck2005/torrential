// Placeholder code, does not work properly
// Change soon

#include <ncurses.h>
#include <string.h>

// Window pointers for different sections
WINDOW *header_win;
WINDOW *main_win;
WINDOW *status_win;

// Initialize colors
void init_color_pairs() {
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Standard text
    init_pair(2, COLOR_BLACK, COLOR_GREEN);  // Highlighted
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Warnings/special
}

// Initialize UI windows
void init_windows() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Create windows
    header_win = newwin(3, max_x, 0, 0);
    main_win = newwin(max_y - 5, max_x, 3, 0);
    status_win = newwin(2, max_x, max_y - 2, 0);

    // Enable scrolling for main window
    scrollok(main_win, TRUE);
}

// Draw header with basic info
void draw_header() {
    wclear(header_win);
    box(header_win, 0, 0);
    wattron(header_win, COLOR_PAIR(1));
    mvwprintw(header_win, 1, 2, "Torrential v0.1.0");
    mvwprintw(header_win, 1, getmaxx(header_win) - 20, "↓ 0 KB/s ↑ 0 KB/s");
    wattroff(header_win, COLOR_PAIR(1));
    wrefresh(header_win);
}

// Draw main content area
void draw_main() {
    wclear(main_win);
    box(main_win, 0, 0);
    wattron(main_win, COLOR_PAIR(1));
    mvwprintw(main_win, 1, 2, "No torrents added yet");
    mvwprintw(main_win, 3, 2, "Press 'o' to open a torrent");
    mvwprintw(main_win, 4, 2, "Press 'q' to quit");
    wattroff(main_win, COLOR_PAIR(1));
    wrefresh(main_win);
}

// Draw status bar
void draw_status() {
    wclear(status_win);
    box(status_win, 0, 0);
    wattron(status_win, COLOR_PAIR(1));
    mvwprintw(status_win, 0, 2, "Status: Idle | DHT: Off | Connected Peers: 0");
    wattroff(status_win, COLOR_PAIR(1));
    wrefresh(status_win);
}

// Handle window resizing
void handle_resize() {
    int new_y, new_x;
    getmaxyx(stdscr, new_y, new_x);

    // Resize and move windows
    wresize(header_win, 3, new_x);
    wresize(main_win, new_y - 5, new_x);
    wresize(status_win, 2, new_x);
    mvwin(status_win, new_y - 2, 0);

    // Redraw everything
    draw_header();
    draw_main();
    draw_status();
}

// Initialize the UI
void init_ui() {
    // Basic curses initialization
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    
    // Colors
    start_color();
    init_color_pairs();
    
    // Create windows
    init_windows();
    
    // Draw initial UI
    draw_header();
    draw_main();
    draw_status();
}

int main() {
    // Initialize UI
    init_ui();
    
    // Main program loop
    while (1) {
        int ch = getch();
        
        switch (ch) {
            case 'q':
                goto cleanup;  // Exit program
            
            case 'o':
                // TODO: Implement torrent file opening
                break;
                
            case KEY_RESIZE:
                handle_resize();
                break;
                
            default:
                break;
        }
    }

cleanup:
    // Clean up windows
    delwin(header_win);
    delwin(main_win);
    delwin(status_win);
    
    // End ncurses
    endwin();
    return 0;
}
