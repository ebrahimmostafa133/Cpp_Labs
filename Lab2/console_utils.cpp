#include "console_utils.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

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

void start_console() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &old_term);
    t = old_term;

    // Raw-ish mode: no canonical input, no echo
    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN]  = 1;
    t.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &t);
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

#endif

// ===================== Common helpers =====================

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void go_xy(i32 x, i32 y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

// ===================== UI Drawing =====================

void draw_menu(const char* items[], i32 count, i32 sel) {
    clear_screen();

    // Simple fixed "virtual" terminal size
    const i32 term_cols = 80;
    const i32 term_rows = 25;

    i32 start_x = (term_cols - MENU_WIDTH) / 2;
    i32 start_y = (term_rows - (count + 7)) / 2;
    if (start_y < 1) start_y = 1;

    i32 y = start_y;

    // Title
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "=======================================" << COLOR_RESET << "\n";
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "|          Simple Menu App            |" << COLOR_RESET << "\n";
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "=======================================" << COLOR_RESET << "\n\n";

    y++;

    // Menu items
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

    // // Help text
    // y++;
    // go_xy(start_x, y++);
    // std::cout << COLOR_TITLE_FG << "---------------------------------------" << COLOR_RESET << "\n";
    // go_xy(start_x, y++);
    // std::cout << "Use UP / DOWN to move, ENTER to select.\n";
    // go_xy(start_x, y++);
    // std::cout << "In content, press BACKSPACE or HOME to go back.\n";
    // go_xy(start_x, y++);
    // std::cout << "Select Exit to quit.\n";
    // go_xy(start_x, y++);
    // std::cout << COLOR_TITLE_FG << "---------------------------------------" << COLOR_RESET << "\n";

    // go_xy(1, term_rows);
    // std::cout << std::flush;
}

void show_content(const char* word) {
    clear_screen();

    const i32 term_cols = 80;
    const i32 term_rows = 25;
    const i32 BOX_W = 30;
    const i32 BOX_H = 5;

    i32 x = (term_cols - BOX_W) / 2;
    i32 y = (term_rows - BOX_H) / 2;
    if (y < 1) y = 1;

    i32 cy = y;

    // Top border
    go_xy(x, cy++);
    std::cout << COLOR_TITLE_FG << std::string(BOX_W, '=') << COLOR_RESET << "\n";

    // Centered word line
    go_xy(x, cy++);
    {
        std::string line = word;
        if ((i32)line.size() < BOX_W) {
            i32 left_pad  = (BOX_W - (i32)line.size()) / 2;
            i32 right_pad = BOX_W - (i32)line.size() - left_pad;
            line = std::string(left_pad, ' ') + line + std::string(right_pad, ' ');
        }
        std::cout << COLOR_TITLE_FG << line << COLOR_RESET << "\n";
    }

    // Bottom border
    go_xy(x, cy++);
    std::cout << COLOR_TITLE_FG << std::string(BOX_W, '=') << COLOR_RESET << "\n";

    // Info
    cy++;
    go_xy(x, cy++);
    std::cout << "Press BACKSPACE or HOME to return to menu.\n";

    go_xy(1, term_rows);
    std::cout << std::flush;
}

// ===================== Main app loop =====================

i32 run_app() {
    const char* items[MENU_ITEM_COUNT] = {"New", "Display", "Exit"};
    i32  sel      = 0;          // which menu item is selected
    i32  mode     = 0;          // 0 = menu, 1 = content
    bool running  = true;       // loop control (no break)

    start_console();

    std::string content_word = "New";  // word shown in content mode

    while (running) {
        if (mode == 0) {
            // MENU MODE
            draw_menu(items, MENU_ITEM_COUNT, sel);
        } else {
            // CONTENT MODE
            show_content(content_word.c_str());
        }

        i32 key = get_key();

        if (mode == 0) {
            // ===== MENU MODE =====
            if (key == KEY_UP) {
                sel = (sel - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            } else if (key == KEY_DOWN) {
                sel = (sel + 1) % MENU_ITEM_COUNT;
            } else if (key == KEY_ENTER) {
                if (sel == 0) {
                    // New
                    content_word = "New";
                    mode = 1;
                } else if (sel == 1) {
                    // Display
                    content_word = "Display";
                    mode = 1;
                } else if (sel == 2) {
                    // Exit
                    running = false;   // no break
                }
            }
        } else {
            // ===== CONTENT MODE =====
            if (key == KEY_BACK || key == KEY_HOME) {
                // Back to menu
                mode = 0;
            }
        }
    }

    stop_console();
    clear_screen();
    std::cout << "Goodbye!\n";
    return 0;
}
