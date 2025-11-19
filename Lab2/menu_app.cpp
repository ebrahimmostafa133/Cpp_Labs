#include <iostream>
#include <cstring>
#include <string>
#include "custom_datatypes.h"
#include "console_utils.h"


// --- Drawing Implementation ---

/**
 * @brief Draws the main menu dashboard to the console, centered horizontally.
 * * @param items Array of menu item strings.
 * @param count The number of items in the array.
 * @param selected The index of the currently selected item.
 */
void draw_dashboard(const char* items[], i32 count, i32 selected) {
    clear_screen();
    
    TerminalSize size = get_terminal_size();
    i32 center_x = (size.cols - MENU_WIDTH) / 2;
    i32 start_y = (size.rows - (count + 6)) / 2; // Calculate top Y to center menu vertically

    // Clamp start_y to a minimum value for terminals that are too short
    if (start_y < 1) start_y = 1;
    
    i32 current_y = start_y;

    // 1. Draw Title
    gotoXY(center_x, current_y++);
    std::cout << ANSI_COLOR_TITLE_FG << "=======================================" << ANSI_COLOR_RESET << "\n";
    gotoXY(center_x, current_y++);
    std::cout << ANSI_COLOR_TITLE_FG << "| Terminal Dashboard (No Curses)      |" << ANSI_COLOR_RESET << "\n";
    gotoXY(center_x, current_y++);
    std::cout << ANSI_COLOR_TITLE_FG << "=======================================" << ANSI_COLOR_RESET << "\n\n";

    current_y++; // Add extra line for separation

    // 2. Draw Menu Items
    for (i32 i = 0; i < count; ++i) {
        gotoXY(center_x, current_y++);
        if (i == selected) {
            // Highlighted item: White text on Blue background
            std::cout << ANSI_COLOR_HIGHLIGHT_BG << ANSI_COLOR_HIGHLIGHT_FG;
            std::cout << " -> " << items[i] << " <- ";
            std::cout << ANSI_COLOR_RESET;
            // Pad with spaces to cover the rest of the line and reset color
            i32 padding = MENU_WIDTH - 7 - (i32)strlen(items[i]); 
            if (padding > 0) std::cout << std::string(padding, ' ');
            std::cout << ANSI_COLOR_RESET;
        } else {
            // Normal item: Green text on default background
            std::cout << ANSI_COLOR_NORMAL_FG;
            std::cout << "    " << items[i] << "    ";
            std::cout << ANSI_COLOR_RESET;
        }
        std::cout << "\n"; // Newline is used here to ensure flush doesn't mess with next gotoXY
    }

    // 3. Draw Instructions
    current_y++; // Add extra line for separation
    gotoXY(center_x, current_y++);
    std::cout << "\n" << ANSI_COLOR_TITLE_FG;
    std::cout << "---------------------------------------" << "\n";
    gotoXY(center_x, current_y++);
    std::cout << "Use UP/DOWN to navigate, ENTER to select." << "\n";
    gotoXY(center_x, current_y++);
    std::cout << "Q to exit. Press BACKSPACE to return from content." << "\n";
    gotoXY(center_x, current_y++);
    std::cout << "---------------------------------------" << ANSI_COLOR_RESET << "\n";

    // Move cursor to a safe place at the bottom
    gotoXY(1, size.rows);

    // Ensure output is immediately visible
    std::cout << std::flush;
}

/**
 * @brief Displays a simple content screen for the selected item, centered.
 * * @param word The menu item name to display.
 */
void display_content_screen(const char* word) {
    clear_screen();
    
    TerminalSize size = get_terminal_size();
    
    // Define the content box properties
    const i32 CONTENT_BOX_WIDTH = 50;
    const i32 CONTENT_BOX_HEIGHT = 8;
    i32 content_x = (size.cols - CONTENT_BOX_WIDTH) / 2;
    i32 content_y = (size.rows - CONTENT_BOX_HEIGHT) / 2;

    if (content_y < 1) content_y = 1;
    
    i32 current_y = content_y;
    
    // 1. Draw Title
    gotoXY(content_x, current_y++);
    std::cout << ANSI_COLOR_TITLE_FG << std::string(CONTENT_BOX_WIDTH, '=') << ANSI_COLOR_RESET << "\n";
    gotoXY(content_x, current_y++);
    std::cout << ANSI_COLOR_TITLE_FG << "| Content for: " << word << std::string(CONTENT_BOX_WIDTH - 15 - strlen(word), ' ') << "|" << ANSI_COLOR_RESET << "\n";
    gotoXY(content_x, current_y++);
    std::cout << ANSI_COLOR_TITLE_FG << std::string(CONTENT_BOX_WIDTH, '=') << ANSI_COLOR_RESET << "\n\n";

    current_y++;
    
    // // 2. Draw Content
    // gotoXY(content_x, current_y++);
    // std::cout << "This is the content screen for: " << ANSI_COLOR_HIGHLIGHT_FG << word << ANSI_COLOR_RESET << ".\n";
    // gotoXY(content_x, current_y++);
    // std::cout << "You can put any application or display logic here." << "\n";
    
    //current_y++;
    
    // 3. Draw Instruction
    gotoXY(content_x, current_y++);
    std::cout << "Press " << ANSI_COLOR_TITLE_FG << "BACKSPACE" << ANSI_COLOR_RESET << " to return to the dashboard." << "\n";

    // Move cursor to a safe place at the bottom
    gotoXY(1, size.rows);

    std::cout << std::flush;
}


/**
 * @brief Main application loop.
 * @return 0 on successful exit.
 */
i32 run_menu_application() {
    const char* items[MENU_ITEM_COUNT] = {"VIEW", "DISPLAY", "EXIT"};
    i32 selected = 0;
    i32 state = 0; // 0: Dashboard (Menu), 1: Content Screen

    // Initialize console for single-key input
    init_console();

    i32 ch;
    while (true) {
        if (state == 0) {
            draw_dashboard(items, MENU_ITEM_COUNT, selected);
        } else {
            display_content_screen(items[selected]);
        }

        ch = get_key();

        if (state == 0) { // Dashboard state: Navigation and Selection
            if (ch == KEY_UP_CUSTOM) {
                selected = (selected - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            }
            else if (ch == KEY_DOWN_CUSTOM) {
                selected = (selected + 1) % MENU_ITEM_COUNT;
            }
            else if (ch == KEY_ENTER_CUSTOM) { // ENTER to select
                if (selected == 2) break; // EXIT
                state = 1; // Change to content screen
            }
        }
        else { // Content Screen state: Return to Dashboard
            if (ch == KEY_BACKSPACE_CUSTOM) {
                state = 0; // Return to Dashboard
            }
        }

        // Always allow 'q' or 'Q' to exit the whole program
        if (ch == KEY_Q_CUSTOM || ch == KEY_Q_UPPER_CUSTOM) break;
    }

    // Restore console settings before exiting
    restore_console();

    // Final output before application closes
    clear_screen();
    std::cout << "\nExiting Application. Goodbye!\n";
    return 0;
}