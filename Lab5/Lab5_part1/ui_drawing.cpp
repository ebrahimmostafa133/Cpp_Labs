#include "ui_drawing.h"
#include "console_io.h"

#include <iostream>
#include <cstring>
#include <string>

// UI
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