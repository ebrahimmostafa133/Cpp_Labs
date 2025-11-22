#include "console_utils.h"

#include <iostream>
#include <cstring>
#include <algorithm> 

void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void go_xy(i32 x, i32 y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

void draw_menu(const char* items[], i32 count, i32 choice) {
    clear_screen();
    const i32 x = 2;
    i32 y = 2;

    go_xy(x, y++);
    std::cout << "--- Main Menu ---\n";
    y++;

    for (i32 i = 0; i < count; ++i) {
        go_xy(x, y++);
        if (i == choice) {
            std::cout << "-> " << items[i] << " <-\n";
        } else {
            std::cout << "   " << items[i] << "\n";
        }
    }

    y++;
    go_xy(x, y++);
    std::cout << "-----------------\n";

    go_xy(1, 25);
    std::cout << std::flush;
}

void draw_save_menu(i32 choice) {
    clear_screen();
    const char* items[] = {"Overwrite Buffer to File", "Append Buffer to File", "Cancel Saving"};
    const i32 x = 2;
    i32 y = 2;

    go_xy(x, y++);
    std::cout << "--- Save Options ---\n";
    y++;

    for (i32 i = 0; i < FILE_MENU_COUNT; ++i) {
        go_xy(x, y++);
        if (i == choice) {
            std::cout << "-> " << items[i] << " <-\n";
        } else {
            std::cout << "   " << items[i] << "\n";
        }
    }

    y++;
    go_xy(x, y++);
    std::cout << "---------------------\n";
    go_xy(x, y++);
    std::cout << "File: " << FILE_NAME << "\n";

    go_xy(1, 25);
    std::cout << std::flush;
}

void show_content(const char* content) {
    clear_screen();

    const i32 rows = 25;
    const i32 x = 5;
    i32 y = 5;

    go_xy(x, y++);
    std::cout << "================================================================\n";
    go_xy(x, y++);
    std::cout << "Contents of " << FILE_NAME << ":\n";
    go_xy(x, y++);
    std::cout << "================================================================\n";
    
    go_xy(x, y++);
    if (std::strlen(content) == 0) {
        std::cout << "FILE IS EMPTY.\n";
    } else {
        std::cout << content << "\n";
    }

    y = rows - 3;
    go_xy(x, y++);
    std::cout << "================================================================\n";
    go_xy(x, y++);
    std::cout << "Press BACKSPACE or HOME to return to menu.\n";

    go_xy(1, rows);
    std::cout << std::flush;
}

void draw_size_prompt() {
    clear_screen();
    const i32 x = 5;
    i32 y = 5;

    go_xy(x, y++);
    std::cout << "===============================\n";
    go_xy(x, y++);
    std::cout << "Enter buffer size (digits only): "; 
    go_xy(x, y++);
    std::cout << "===============================\n";

    go_xy(x + 33, 6); 
    std::cout << std::flush;
}

void draw_editor(const char* buffer, i32 current_size, i32 max_size, i32 cursor_pos) {
    clear_screen();
    const i32 x = 5;
    i32 y = 5;

    go_xy(x, y++);
    std::cout << "--- String Editor ---\n";

    go_xy(x, y++);
    std::cout << "Max Size: " << max_size << " | Current Size: " << current_size << "\n";
    y++;
    
    go_xy(x, y++);
    std::cout << "Buffer: [";
    for (i32 i = 0; i < current_size; ++i) {
        std::cout << buffer[i];
    }
    std::cout << "]\n";
    
    go_xy(x + 9 + cursor_pos, y++);
    std::cout << "^\n";
    
    y++;
    go_xy(x, y++);
    std::cout << "-------------------------------------------\n";
    go_xy(x, y++);
    std::cout << "Keys: LEFT/RIGHT, BACKSPACE.\n";
    go_xy(x, y++);
    std::cout << "Press HOME to save buffer to file.\n";
    go_xy(x, y++);
    std::cout << "Start typing to insert a character.\n";

    go_xy(1, 25);
    std::cout << std::flush;
}
