#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include "custom_types.h"

// Colors (ANSI)
#define COLOR_RESET      "\033[0m"
#define COLOR_HL_BG      "\033[44m"  // Blue background
#define COLOR_HL_FG      "\033[37m"  // White text
#define COLOR_NORMAL_FG  "\033[32m"  // Green text
#define COLOR_TITLE_FG   "\033[33m"  // Yellow text

// Simple key codes
#define KEY_UP     1001
#define KEY_DOWN   1002
#define KEY_ENTER  1003
#define KEY_BACK   1004
#define KEY_Q      'q'
#define KEY_Q_UP   'Q'

#define MENU_ITEM_COUNT 3
#define MENU_WIDTH      39

typedef struct {
    i32 rows;
    i32 cols;
} TermSize;

void clear_screen();
void go_xy(i32 x, i32 y);
TermSize get_term_size();
void start_console();
void stop_console();
i32 get_key();

void draw_menu(const char* items[], i32 count, i32 sel);
void show_content(const char* word);
i32 run_app();

#endif
