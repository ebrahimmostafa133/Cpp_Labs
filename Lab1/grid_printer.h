#ifndef GRID_PRINTER_H
#define GRID_PRINTER_H

#include "custom_datatypes.h" 
#include <string>

void init_ncurses();

bool_t setup_colors();

void gotoxy(i32 y, i32 x);

void draw_frame();

i32 run_grid_printer(i32 sleep_duration_seconds);

#endif // GRID_PRINTER_H