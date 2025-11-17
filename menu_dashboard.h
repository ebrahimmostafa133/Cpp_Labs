#ifndef MENU_DASHBOARD_H
#define MENU_DASHBOARD_H

#include "custom_datatypes.h"
// NOTE: ncurses/pdcurses is included in the .cpp files where needed.

#define COLOR_PAIR_HIGHLIGHT 5
#define MENU_ITEM_COUNT 3

// Function declarations are kept the same
void init_ncurses();
bool_t setup_colors();
void gotoxy(i32 y, i32 x);
void draw_frame();

void init_screen();
void draw_dashboard(const char* items[], i32 count, i32 selected);
void display_content_screen(const char* word);
i32 run_menu_application();

#endif