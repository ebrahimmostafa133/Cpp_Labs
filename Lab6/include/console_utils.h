#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include "custom_types.h"
#include <string>

#define KEY_UP       1001
#define KEY_DOWN     1002
#define KEY_ENTER    1003
#define KEY_BACK     1004
#define KEY_HOME     1005
#define KEY_LEFT     1006 
#define KEY_RIGHT    1007 
#define KEY_OTHER    1999

#define MENU_COUNT 3
#define FILE_MENU_COUNT 3

#define MODE_MENU           0
#define MODE_CONTENT        1
#define MODE_GET_SIZE       2 
#define MODE_EDIT_STRING    3
#define MODE_FILE_OPTIONS   4 

#define FILE_NAME "app_data.txt"

void start_console();
void stop_console();
void clear_screen();
void go_xy(i32 x, i32 y);
i32  get_key();

void* allocate_memory(u32 size);
void  free_memory(void* ptr);

i32 save_overwrite(const char* name, const char* data, i32 size); 
i32 save_append(const char* name, const char* data, i32 size);    
std::string read_file(const char* name);

void draw_menu(const char* items[], i32 count, i32 choice);
void draw_save_menu(i32 choice);
void show_content(const char* content);
void draw_size_prompt();
void draw_editor(const char* buffer, i32 current_size, i32 max_size, i32 cursor_pos);

i32  run_app();

#endif
