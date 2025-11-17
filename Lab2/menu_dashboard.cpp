/*
 * File: menu_dashboard.cpp
 * Description: A single-file, cross-platform C++ terminal menu application using curses.
 * Includes a fix to prevent the console window from immediately closing on Windows.
 */

#include <iostream>
#include <curses.h> // Includes ncurses.h or pdcurses.h
#include <cstring>  // For strlen
#include <cstdlib>  // For EXIT_SUCCESS

// --- Custom Datatypes (Embedded Declarations) ---
typedef int                 i32;
typedef int                 bool_t; // 0=false, non-zero=true

// --- Menu Configuration ---
#define COLOR_PAIR_HIGHLIGHT 5
#define MENU_ITEM_COUNT 3

// --- Function Prototypes (Internal) ---
void init_ncurses();
bool_t setup_colors();
void init_screen();
void draw_dashboard(const char* items[], i32 count, i32 selected);
void display_content_screen(const char* word);
i32 run_menu_application();

// --- Utility Functions Implementation ---

// Initializes the ncurses environment
void init_ncurses() {
    initscr();
    cbreak();    // Line buffering disabled
    noecho();    // Don't echo input
    curs_set(0); // Hide cursor
    clear();
}

// Sets up color pairs
bool_t setup_colors() {
    if (has_colors()) {
        start_color();
        // Highlight color: Yellow text on Black background
        init_pair(COLOR_PAIR_HIGHLIGHT, COLOR_YELLOW, COLOR_BLACK);
        // Normal text color: Green text on Black background
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        // Content screen color: Cyan text on Black background
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        return 1;
    }
    return 0;
}

// Initial screen setup
void init_screen() {
    init_ncurses();
    setup_colors();
    // Enable special keys (like arrow keys, home, end, etc.)
    keypad(stdscr, TRUE); 
}

// --- Menu Functions Implementation ---

// Draws the main menu dashboard (NEW, DISPLAY, EXIT)
void draw_dashboard(const char* items[], i32 count, i32 selected) {
    clear(); 

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    i32 start_y = max_y / 2 - (count * 2) / 2;
    
    for (i32 i = 0; i < count; ++i) {
        i32 y = start_y + i * 2;
        size_t len = strlen(items[i]);
        i32 x = (max_x - (i32)len) / 2;

        if (i == selected) {
            attron(A_BOLD | A_REVERSE | COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
            mvprintw(y, x, "%s", items[i]);
            attroff(A_BOLD | A_REVERSE | COLOR_PAIR(COLOR_PAIR_HIGHLIGHT));
        } else {
            attron(COLOR_PAIR(2));
            mvprintw(y, x, "%s", items[i]);
            attroff(COLOR_PAIR(2));
        }
    }

    // Instructions
    attron(A_BOLD);
    mvprintw(max_y - 3, 5, "Use UP/DOWN, ENTER to select. EXIT to quit.");
    attroff(A_BOLD);
    refresh();
}

// Draws the "NEW" or "DISPLAY" content screen
void display_content_screen(const char* word) {
    clear(); 

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    i32 x = (max_x - (i32)strlen(word)) / 2;
    i32 y = max_y / 2;

    attron(A_BOLD | COLOR_PAIR(4));
    mvprintw(y, x, "%s", word);
    attroff(A_BOLD | COLOR_PAIR(4));

    // Instructions for returning
    attron(A_BOLD);
    mvprintw(max_y - 2, 5, "Press BACKSPACE, HOME, or any ARROW key to return.");
    attroff(A_BOLD);

    refresh();
}

// --- Main Application Logic ---

i32 run_menu_application() {
    init_screen();

    const char* items[MENU_ITEM_COUNT] = {"NEW", "DISPLAY", "EXIT"};
    i32 selected = 0;
    i32 state = 0; // 0: Dashboard (Menu), 1: Content Screen

    int ch;
    while (true) {
        if (state == 0) {
            draw_dashboard(items, MENU_ITEM_COUNT, selected);
        } else {
            display_content_screen(items[selected]);
        }

        ch = getch();

        if (state == 0) { // Dashboard state: Navigation and Selection
            if (ch == KEY_UP) selected = (selected - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            else if (ch == KEY_DOWN) selected = (selected + 1) % MENU_ITEM_COUNT;
            else if (ch == '\n' || ch == KEY_ENTER) { // ENTER to select
                if (selected == 2) break; // EXIT
                state = 1;
            }
        } 
        else { // Content Screen state: Return to Dashboard
            if (ch == KEY_BACKSPACE || ch == 127 || ch == 8 ||
                ch == KEY_HOME || ch == KEY_END || 
                ch == KEY_UP || ch == KEY_DOWN || 
                ch == KEY_LEFT || ch == KEY_RIGHT) {
                state = 0; // Return to Dashboard
            }
        }
        
        // Always allow 'q' or 'Q' to exit the whole program
        if (ch == 'q' || ch == 'Q') break; 
    }
    
    // *** FIX: Added delay for Windows console ***
    mvprintw(LINES - 1, 0, "Program finished. Press any key to exit.");
    refresh();
    getch(); 

    endwin(); // Restore the terminal
    return EXIT_SUCCESS;
}

int main() {
    return run_menu_application();
}