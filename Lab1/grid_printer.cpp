#include "grid_printer.h"
#include <ncurses.h>
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
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        init_pair(5, COLOR_YELLOW, COLOR_BLACK);
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

i32 run_grid_printer(i32 sleep_duration_seconds) {
    init_ncurses();
    setup_colors();

    draw_frame();
    gotoxy(2, 5);
    printw("--- Phase 1: Colorful Display ---");

    attron(COLOR_PAIR(1));
    gotoxy(6, 10);
    printw("1. This phrase is RED.");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    gotoxy(8, 10);
    printw("2. This phrase is GREEN.");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    gotoxy(10, 10);
    printw("3. This phrase is BLUE.");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(5));
    gotoxy(20, 5);
    printw("ACTION: wait (Screen will clear in %d seconds...)", sleep_duration_seconds);
    attroff(COLOR_PAIR(5));
    
    refresh();

    std::this_thread::sleep_for(std::chrono::seconds(sleep_duration_seconds));

    clear();
    
    draw_frame();
    gotoxy(2, 5);
    printw("--- Phase 2: After Screen Clear ---");

    attron(COLOR_PAIR(4));
    gotoxy(6, 10);
    printw("Screen Cleared! New content in CYAN (Pair 4).");
    gotoxy(8, 10);
    printw("The display was successfully refreshed.");
    attroff(COLOR_PAIR(4));

    gotoxy(20, 5);
    printw("ACTION: wait (Press any key to restore terminal...)");

    refresh();

    getch();

    endwin();

    return 0;
}