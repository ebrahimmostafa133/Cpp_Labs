#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include "custom_types.h"
#include <string>

// Colors (ANSI)
#define COLOR_RESET      "\033[0m"
#define COLOR_HL_BG      "\033[44m"  // Blue background
#define COLOR_HL_FG      "\033[37m"  // White text
#define COLOR_NORMAL_FG  "\033[32m"  // Green text
#define COLOR_TITLE_FG   "\033[33m"  // Yellow text

// Key codes (custom)
#define KEY_UP       1001
#define KEY_DOWN     1002
#define KEY_ENTER    1003
#define KEY_BACK     1004
#define KEY_HOME     1005
#define KEY_OTHER    1999

#define MENU_ITEM_COUNT 3
#define MENU_WIDTH      39

// Simple employee struct
typedef struct {
    std::string first_name;
    std::string last_name;
    int         age;
    std::string gender;
} Employee;

// Console helpers
void start_console();
void stop_console();
void clear_screen();
void go_xy(i32 x, i32 y);
i32  get_key();

// UI
void draw_menu(const char* items[], i32 count, i32 sel);

// Employee screens
void add_employee(Employee* employees, int& count, int max_count);
void show_employees(const Employee* employees, int count);

// Main loop
i32  run_app();

#endif
