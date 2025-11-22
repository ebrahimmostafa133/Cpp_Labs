#include "console_io.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#if defined(_WIN32) || defined(_WIN64)
// ===================== Windows =====================
#include <conio.h>
#include <windows.h>

void start_console() {
    // Enable ANSI escape sequences on newer Windows consoles
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}

void stop_console() {
    // Nothing special to restore here
}

i32 get_key() {
    int ch = _getch();

    // Enter
    if (ch == '\r') return KEY_ENTER;
    // Backspace
    if (ch == 8)    return KEY_BACK;

    // Extended keys
    if (ch == 0 || ch == 0xE0) {
        ch = _getch();
        if (ch == 72) return KEY_UP;      // Up arrow
        if (ch == 80) return KEY_DOWN;    // Down arrow
        if (ch == 71) return KEY_HOME;    // Home
        return KEY_OTHER;
    }

    return ch;
}

#else
// ===================== Linux / macOS =====================

#include <termios.h>
#include <unistd.h>

static struct termios old_term;
static struct termios raw_term;

void start_console() {
    tcgetattr(STDIN_FILENO, &old_term);
    raw_term = old_term;

    // Raw-ish mode: no canonical input, no echo
    raw_term.c_lflag &= ~(ICANON | ECHO);
    raw_term.c_cc[VMIN]  = 1;
    raw_term.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw_term);
}

void stop_console() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

i32 get_key() {
    int ch = getchar();

    // ESC sequence for arrows / home
    if (ch == 0x1B) {          // ESC
        int seq1 = getchar();
        if (seq1 == '[') {
            int seq2 = getchar();
            if (seq2 == 'A') return KEY_UP;    // Up
            if (seq2 == 'B') return KEY_DOWN;  // Down
            if (seq2 == 'H') return KEY_HOME;  // Home (ESC [ H)

            // Some terminals send ESC [ 1 ~ for Home
            if (seq2 == '1') {
                int seq3 = getchar();
                if (seq3 == '~') return KEY_HOME;
            }
        }
        return KEY_OTHER;
    }

    if (ch == '\n' || ch == '\r') return KEY_ENTER;
    if (ch == 127 || ch == 8)     return KEY_BACK;   // Backspace

    return ch;
}

// helpers to temporarily switch between raw and normal input on Linux
void set_raw_mode(bool raw) {
    if (raw) {
        tcsetattr(STDIN_FILENO, TCSANOW, &raw_term);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    }
}

#endif

// ===================== Common helpers =====================

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void go_xy(i32 x, i32 y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}