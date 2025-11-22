#ifndef CONSOLE_IO_H
#define CONSOLE_IO_H

#include "../custom_types.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
// Key codes (custom)
#define KEY_UP       1001
#define KEY_DOWN     1002
#define KEY_ENTER    1003
#define KEY_BACK     1004
#define KEY_HOME     1005
#define KEY_OTHER    1999

// Console helpers (OS-dependent)
void start_console();
void stop_console();
i32  get_key();

// Common screen helpers
void clear_screen();
void go_xy(i32 x, i32 y);

#if !defined(_WIN32) && !defined(_WIN64)
// Linux-specific helper
void set_raw_mode(bool raw);
#endif

#endif // CONSOLE_IO_H