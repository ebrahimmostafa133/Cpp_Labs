#include "menu_dashboard.h" 
// Use the standard <curses.h> which resolves to ncurses.h on Linux
// and pdcurses.h on Windows/MinGW when set up correctly.
#include <curses.h> 
#include <thread>
#include <chrono>

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    clear();
}

bool_t setup_colors() {
    if (has_colors()) {
        start_color();
        // Define color pairs 1-4
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        // Define color pair 5 for menu highlight
        init_pair(COLOR_PAIR_HIGHLIGHT, COLOR_YELLOW, COLOR_BLACK);
        return true;
    }
    return false;
}

void gotoxy(i32 y, i32 x) {
    move(y, x);
}

void draw_frame() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    for (int i = 0; i < max_x; ++i) {
        mvprintw(0, i, "-");
        mvprintw(max_y - 1, i, "-");
    }

    for (int i = 0; i < max_y; ++i) {
        mvprintw(i, 0, "|");
        mvprintw(i, max_x - 1, "|");
    }
}