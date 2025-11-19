#include "console_utils.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

#if defined(_WIN32) || defined(_WIN64)

// ---------------- Windows ----------------
#include <conio.h>
#include <windows.h>

void start_console() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
}

void stop_console() {
    // nothing for now
}

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void go_xy(i32 x, i32 y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

TermSize get_term_size() {
    TermSize s = {25, 80};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (GetConsoleScreenBufferInfo(hOut, &info)) {
        s.cols = info.srWindow.Right - info.srWindow.Left + 1;
        s.rows = info.srWindow.Bottom - info.srWindow.Top + 1;
    }
    return s;
}

i32 get_key() {
    i32 ch = _getch();

    if (ch == '\r') return KEY_ENTER;
    if (ch == '\b') return KEY_BACK;

    if (ch == 0 || ch == 0xE0) {
        ch = _getch();
        if (ch == 72) return KEY_UP;
        if (ch == 80) return KEY_DOWN;
        return 0;
    }
    return ch;
}

#else

// ---------------- Linux / macOS ----------------
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

static struct termios old_term;

void start_console() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &old_term);
    t = old_term;

    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN]  = 1;
    t.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void stop_console() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void go_xy(i32 x, i32 y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

TermSize get_term_size() {
    TermSize s = {25, 80};
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
        s.rows = ws.ws_row;
        s.cols = ws.ws_col;
    }
    return s;
}

i32 get_key() {
    i32 ch = getchar();

    if (ch == 0x1B) {
        struct termios cur, tmp;
        tcgetattr(STDIN_FILENO, &cur);
        tmp = cur;
        tmp.c_cc[VMIN] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &tmp);

        i32 seq1 = getchar();
        i32 seq2 = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &cur);

        if (seq1 == '[') {
            if (seq2 == 'A') return KEY_UP;
            if (seq2 == 'B') return KEY_DOWN;
        }
        return 0;
    }

    if (ch == '\n' || ch == '\r') return KEY_ENTER;
    if (ch == 127 || ch == 8)     return KEY_BACK;

    return ch;
}

#endif

// ---------------- Drawing ----------------

#include <cstring>
#include <string>

void draw_menu(const char* items[], i32 count, i32 sel) {
    clear_screen();

    TermSize s = get_term_size();
    i32 start_x = (s.cols - MENU_WIDTH) / 2;
    i32 start_y = (s.rows - (count + 6)) / 2;
    if (start_y < 1) start_y = 1;

    i32 y = start_y;

    // Title
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "=======================================" << COLOR_RESET << "\n";
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "|       Simple Terminal Menu          |" << COLOR_RESET << "\n";
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "=======================================" << COLOR_RESET << "\n\n";

    y++;

    // Items
    for (i32 i = 0; i < count; ++i) {
        go_xy(start_x, y++);
        if (i == sel) {
            std::cout << COLOR_HL_BG << COLOR_HL_FG;
            std::cout << " -> " << items[i] << " <- ";
            std::cout << COLOR_RESET;

            i32 pad = MENU_WIDTH - 7 - (i32)std::strlen(items[i]);
            if (pad > 0) std::cout << std::string(pad, ' ');
        } else {
            std::cout << COLOR_NORMAL_FG;
            std::cout << "    " << items[i] << "    ";
            std::cout << COLOR_RESET;
        }
        std::cout << "\n";
    }

    // Help text
    y++;
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "---------------------------------------" << COLOR_RESET << "\n";
    go_xy(start_x, y++);
    std::cout << "Use UP / DOWN, ENTER to select." << "\n";
    go_xy(start_x, y++);
    std::cout << "Press Q to quit. BACKSPACE from content." << "\n";
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "---------------------------------------" << COLOR_RESET << "\n";

    go_xy(1, s.rows);
    std::cout << std::flush;
}

void show_content(const char* word) {
    clear_screen();

    TermSize s = get_term_size();
    const i32 BOX_W = 50;
    const i32 BOX_H = 7;

    i32 x = (s.cols - BOX_W) / 2;
    i32 y = (s.rows - BOX_H) / 2;
    if (y < 1) y = 1;

    i32 cy = y;

    // Top
    go_xy(x, cy++);
    std::cout << COLOR_TITLE_FG << std::string(BOX_W, '=') << COLOR_RESET << "\n";

    // Title line
    go_xy(x, cy++);
    std::string title = "| Content: ";
    title += word;
    std::string line = title;
    if ((int)line.size() < BOX_W - 1) {
        line += std::string(BOX_W - 1 - line.size(), ' ');
    }
    line += "|";
    std::cout << COLOR_TITLE_FG << line << COLOR_RESET << "\n";

    // Separator
    go_xy(x, cy++);
    std::cout << COLOR_TITLE_FG << std::string(BOX_W, '=') << COLOR_RESET << "\n\n";

    cy++;
    go_xy(x, cy++);
    std::cout << "This is a simple content screen for: " << word << "\n";
    go_xy(x, cy++);
    std::cout << "Press BACKSPACE to go back to the menu.\n";

    go_xy(1, s.rows);
    std::cout << std::flush;
}

// ---------------- Main app loop ----------------

i32 run_app() {
    const char* items[MENU_ITEM_COUNT] = {"VIEW", "DISPLAY", "EXIT"};
    i32 sel   = 0;
    i32 mode  = 0; // 0 = menu, 1 = content

    start_console();

    while (true) {
        if (mode == 0) {
            draw_menu(items, MENU_ITEM_COUNT, sel);
        } else {
            show_content(items[sel]);
        }

        i32 ch = get_key();

        if (mode == 0) {
            if (ch == KEY_UP) {
                sel = (sel - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            } else if (ch == KEY_DOWN) {
                sel = (sel + 1) % MENU_ITEM_COUNT;
            } else if (ch == KEY_ENTER) {
                if (sel == 2) break;  // EXIT
                mode = 1;
            }
        } else {
            if (ch == KEY_BACK) {
                mode = 0;
            }
        }

        if (ch == KEY_Q || ch == KEY_Q_UP) break;
    }

    stop_console();
    clear_screen();
    std::cout << "Goodbye!\n";
    return 0;
}


