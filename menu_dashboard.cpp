#include "menu_dashboard.h"
#include <cstring>
#include <chrono>
#include <thread>
// Include <curses.h> for Curses functions
#include <curses.h> 

void init_screen() {
    // 1. Initialize ncurses screen settings
    init_ncurses();
    
    // 2. Setup colors
    setup_colors();

    // 3. Enable special keys for the terminal dashboard
    keypad(stdscr, TRUE); 
}

void draw_dashboard(const char* items[], i32 count, i32 selected) {
    clear();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Title
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(2, 5, "Terminal Dashboard"); 
    attroff(A_BOLD | COLOR_PAIR(1));

    // Find max width
    size_t max_len = 0;
    for (i32 i = 0; i < count; ++i) {
        size_t len = strlen(items[i]);
        if (len > max_len) max_len = len;
    }

    size_t full_width = max_len + 6;
    int start_x = (max_x - (int)full_width) / 2; // Cast full_width to int
    int start_y = max_y / 2 - 2;

    // Draw menu items
    for (i32 i = 0; i < count; ++i) {
        int y = start_y + i * 2;
        size_t len = strlen(items[i]);

        if (i == selected) {
            size_t padL = (max_len - len) / 2;
            size_t padR = max_len - len - padL;

            attron(A_REVERSE | COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
            mvprintw(y, start_x, "-> ");
            // Use (int) for printw width specifiers
            mvprintw(y, start_x + 3, "%*s", (int)padL, ""); 
            printw("%s", items[i]);
            printw("%*s <-", (int)padR, "");
            attroff(A_REVERSE | COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
        } else {
            size_t pad = full_width - len;
            size_t padL = pad / 2;
            size_t padR = pad - padL;

            attron(A_BOLD | COLOR_PAIR(2));
            mvprintw(y, start_x, "%*s%s%*s", (int)padL, "", items[i], (int)padR, "");
            attroff(A_BOLD | COLOR_PAIR(2));
        }
    }

    mvprintw(max_y - 3, 5, "Use UP/DOWN, ENTER to select. Q/F10 to exit.");
    refresh();
}

void display_content_screen(const char* word) {
    clear();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    attron(COLOR_PAIR(4));
    mvprintw(max_y / 2, (max_x - (int)strlen(word)) / 2, "%s", word);
    attroff(COLOR_PAIR(4));

    attron(A_BOLD);
    mvprintw(max_y - 2, 5, "Press BACKSPACE to return.");
    attroff(A_BOLD);

    refresh();
}

i32 run_menu_application() {
    init_screen();

    const char* items[MENU_ITEM_COUNT] = {"NEW", "DISPLAY", "EXIT"};
    i32 selected = 0;
    i32 state = 0; // 0: Dashboard, 1: Content Screen

    int ch;
    while (true) {
        if (state == 0)
            draw_dashboard(items, MENU_ITEM_COUNT, selected);

        ch = getch();

        if (state == 0) { // Dashboard state
            if (ch == KEY_UP) selected = (selected - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            else if (ch == KEY_DOWN) selected = (selected + 1) % MENU_ITEM_COUNT;
            else if (ch == '\n' || ch == KEY_ENTER) {
                if (selected == 2) break; // EXIT
                state = 1;
                display_content_screen(items[selected]);
            }
            else if (ch == 'q' || ch == 'Q' || ch == KEY_F(10)) break;
        } 
        else { // Content Screen state
            // PDCurses sometimes reports KEY_BACKSPACE, and sometimes 127
            if (ch == KEY_BACKSPACE || ch == 127 || ch == 8 || ch ==0x08) state = 0; 
            if (ch == 'q' || ch == 'Q' || ch == KEY_F(10)) break;
        }
    }

    endwin();
    return 0;
}