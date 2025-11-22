#ifndef UI_DRAWING_H
#define UI_DRAWING_H

#include "custom_types.h"

// Colors (ANSI)
#define COLOR_RESET      "\033[0m"
#define COLOR_HL_BG      "\033[44m"  // Blue background
#define COLOR_HL_FG      "\033[37m"  // White text
#define COLOR_NORMAL_FG  "\033[32m"  // Green text
#define COLOR_TITLE_FG   "\033[33m"  // Yellow text

// UI constants
#define MENU_ITEM_COUNT 3
#define MENU_WIDTH      39

// UI
void draw_menu(const char* items[], i32 count, i32 sel);

#endif // UI_DRAWING_H