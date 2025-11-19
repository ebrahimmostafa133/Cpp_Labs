#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include "custom_datatypes.h"
#include <string>

// --- ANSI Escape Codes for Styling ---
#define ANSI_COLOR_RESET    "\033[0m"
#define ANSI_COLOR_HIGHLIGHT_BG "\033[44m" // Blue Background
#define ANSI_COLOR_HIGHLIGHT_FG "\033[37m" // White Foreground
#define ANSI_COLOR_NORMAL_FG "\033[32m"    // Green Foreground
#define ANSI_COLOR_TITLE_FG "\033[33m"     // Yellow Foreground

// --- Key Codes (Simplified, non-curses) ---
// We'll use simple integer values for special keys for cross-platform consistency
#define KEY_UP_CUSTOM    1001
#define KEY_DOWN_CUSTOM  1002
#define KEY_ENTER_CUSTOM 1003
#define KEY_BACKSPACE_CUSTOM 1004
#define KEY_Q_CUSTOM     'q'
#define KEY_Q_UPPER_CUSTOM 'Q'


// --- Menu Configuration ---
#define MENU_ITEM_COUNT 3
#define MENU_WIDTH 39 // Width of the border line "======================================="


// Structure to hold terminal dimensions
typedef struct {
    i32 rows;
    i32 cols;
} TerminalSize;


// --- Function Prototypes ---

// Clears the console screen using system-dependent commands or ANSI.
void clear_screen();

// Moves the cursor to the specified column (x) and row (y).
// Uses ANSI escape sequence: \033[{y};{x}H. (Note: ANSI uses Y,X convention)
void gotoXY(i32 x, i32 y);

// Gets the current width and height of the terminal window.
TerminalSize get_terminal_size();

// Initializes the console for single-key input (disables echoing and buffering).
void init_console();

// Restores the console settings (re-enables echoing and buffering).
void restore_console();

// Gets a single character from input and returns a mapped key code.
// Handles special keys like Up/Down arrow.
i32 get_key();



// --- Function Prototypes for the Menu Application ---

/**
 * @brief Draws the main menu dashboard to the console.
 * @param items Array of menu item strings.
 * @param count The number of items in the array.
 * @param selected The index of the currently selected item.
 */

void draw_dashboard(const char* items[], i32 count, i32 selected);

/**
 * @brief Displays a simple content screen for the selected item.
 * @param word The menu item name to display.
 */
void display_content_screen(const char* word);

/**
 * @brief Main application loop that drives the menu interaction.
 * @return 0 on successful exit.
 */
i32 run_menu_application();

#endif // CONSOLE_UTILS_H