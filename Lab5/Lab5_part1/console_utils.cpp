#include "console_utils.h"

#include <string>      // <-- add this
#include <limits> 
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
static void set_raw_mode(bool raw) {
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
    std::cout << COLOR_TITLE_FG << "|         Employee Manager            |" << COLOR_RESET << "\n";
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

    // Help text
    y++;
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "---------------------------------------" << COLOR_RESET << "\n";
    go_xy(start_x, y++);
    std::cout << "Use UP / DOWN to move, ENTER to select.\n";
    go_xy(start_x, y++);
    std::cout << "New     - add employee\n";
    go_xy(start_x, y++);
    std::cout << "Display - show all employees\n";
    go_xy(start_x, y++);
    std::cout << "Exit    - quit\n";
    go_xy(start_x, y++);
    std::cout << COLOR_TITLE_FG << "---------------------------------------" << COLOR_RESET << "\n";

    go_xy(1, term_rows);
    std::cout << std::flush;
}

// ===================== Employee Screens =====================

// Small helper: read a line from stdin in "normal" mode
static std::string read_line() {
    std::string line;

#if defined(_WIN32) || defined(_WIN64)
    std::getline(std::cin, line);
#else
    // switch to normal (cooked) mode temporarily
    set_raw_mode(false);
    std::getline(std::cin, line);
    set_raw_mode(true);
#endif

    return line;
}

void add_employee(Employee* employees, int& count, int max_count) {
    clear_screen();

    if (count >= max_count) {
        std::cout << "Employee list is full (" << max_count << "). Press ENTER to continue...";
        std::cout.flush();

        // temporarily use normal input for this pause
#if defined(_WIN32) || defined(_WIN64)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
        set_raw_mode(false);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_raw_mode(true);
#endif
        return;
    }

    std::cout << "=== Add New Employee ===\n\n";

#if defined(_WIN32) || defined(_WIN64)
    // clear leftover newline from previous getch-based input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
    set_raw_mode(false);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif

    Employee emp;

    std::cout << "First name : ";
    std::getline(std::cin, emp.first_name);

    std::cout << "Last name  : ";
    std::getline(std::cin, emp.last_name);

    std::cout << "Age        : ";
    std::string age_str;
    std::getline(std::cin, age_str);
    emp.age = std::atoi(age_str.c_str());

    std::cout << "Gender     : ";
    std::getline(std::cin, emp.gender);

#if !defined(_WIN32) && !defined(_WIN64)
    // back to raw mode on Linux
    set_raw_mode(true);
#endif

    employees[count] = emp;
    count++;

    std::cout << "\nEmployee added. Press ENTER to return to menu...";
    std::cout.flush();

#if defined(_WIN32) || defined(_WIN64)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
    set_raw_mode(false);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    set_raw_mode(true);
#endif
}

void show_employees(const Employee* employees, int count) {
    clear_screen();

    std::cout << "=== Employee List ===\n\n";

    if (count == 0) {
        std::cout << "No employees yet.\n";
    } else {
        for (int i = 0; i < count; ++i) {
            std::cout << "Employee #" << (i + 1) << ":\n";
            std::cout << "  First name : " << employees[i].first_name << "\n";
            std::cout << "  Last name  : " << employees[i].last_name  << "\n";
            std::cout << "  Age        : " << employees[i].age        << "\n";
            std::cout << "  Gender     : " << employees[i].gender     << "\n";
            std::cout << "----------------------------------------\n";
        }
    }

    std::cout << "\nPress BACKSPACE or HOME to return to menu.\n";
    std::cout.flush();

    bool in_display = true;
    while (in_display) {
        i32 key = get_key();
        if (key == KEY_BACK || key == KEY_HOME) {
            in_display = false;
        }
    }
}

// ===================== Main app loop =====================

i32 run_app() {
    const char* items[MENU_ITEM_COUNT] = {"New", "Display", "Exit"};
    i32  sel      = 0;          // which menu item is selected
    bool running  = true;       // loop control (no break)

    // simple employee storage
    const int MAX_EMPLOYEES = 100;
    Employee employees[MAX_EMPLOYEES];
    int employee_count = 0;

    start_console();

    while (running) {
        draw_menu(items, MENU_ITEM_COUNT, sel);

        i32 key = get_key();

        // ===== MENU MODE (we always return here after actions) =====
        if (key == KEY_UP) {
            sel = (sel - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
        } else if (key == KEY_DOWN) {
            sel = (sel + 1) % MENU_ITEM_COUNT;
        } else if (key == KEY_ENTER) {
            if (sel == 0) {
                // New -> add employee
                add_employee(employees, employee_count, MAX_EMPLOYEES);
            } else if (sel == 1) {
                // Display -> show all employees
                show_employees(employees, employee_count);
            } else if (sel == 2) {
                // Exit
                running = false;   // no break
            }
        }
    }

    stop_console();
    clear_screen();
    std::cout << "Goodbye!\n";
    return 0;
}
