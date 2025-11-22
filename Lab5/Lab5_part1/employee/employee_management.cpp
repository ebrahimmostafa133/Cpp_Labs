#include "../console/console_io.h"     // Contains start/stop_console, get_key, set_raw_mode
#include "../ui/ui_drawing.h"          // Contains clear_screen, draw_* functions
#include "employee_management.h"       // Assuming this defines the Employee struct and MAX_COUNT

#include <iostream>                    // For std::cout, std::cin, std::getline
#include <string>                      // For std::string
#include <limits>                      // For std::numeric_limits
#include <cstdlib>                     // For std::atoi

// --- Helper for Safe Line Reading ---

/**
 * @brief Reads a line of input from standard input, temporarily restoring normal terminal mode if necessary.
 * @return std::string The line read from stdin.
 */
static std::string read_line() {
    std::string line;

#if defined(_WIN32) || defined(_WIN64)
    // On Windows, the initial terminal setup (start_console) enables ANSI, 
    // but input generally stays in a recoverable state, so we just use getline.
    std::getline(std::cin, line);
#else
    // On Linux/macOS, input must be switched from raw mode (used for menu/editor)
    // back to normal mode (canonical/cooked mode) to enable buffering for getline.
    set_raw_mode(false); // Switch to normal mode (waits for ENTER)
    std::getline(std::cin, line);
    set_raw_mode(true);  // Switch back to raw mode (key-by-key)
#endif

    return line;
}

// --- Main Application Functions ---

/**
 * @brief Handles the interactive process of adding a new employee to the array.
 * @param employees The array of Employee structs.
 * @param count Reference to the current number of employees.
 * @param max_count The maximum capacity of the employee array.
 */
void add_employee(Employee* employees, int& count, int max_count) {
    clear_screen();

    // 1. Capacity Check
    if (count >= max_count) {
        std::cout << "Employee list is full (" << max_count << "). Press ENTER to continue...";
        std::cout.flush();

        // Use normal input buffer clearing and waiting for a pause.
#if defined(_WIN32) || defined(_WIN64)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
        set_raw_mode(false); // Temporarily switch to normal mode for buffered input wait.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        set_raw_mode(true);  // Restore raw mode.
#endif
        return;
    }

    std::cout << "=== Add New Employee ===\n\n";

    // 2. Clear Residual Input Buffer
    // This handles leftover newline characters from previous raw input (like ENTER keypress).
#if defined(_WIN32) || defined(_WIN64)
    // Clear leftover newline from previous getch-based input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
    // Must switch to normal mode to use std::cin.ignore reliably.
    set_raw_mode(false);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif

    Employee emp;

    // 3. Collect Data (Input Phase - requires normal mode)

    std::cout << "First name : ";
    // std::getline needs normal (cooked) mode to handle line input properly.
    std::getline(std::cin, emp.first_name);

    std::cout << "Last name  : ";
    std::getline(std::cin, emp.last_name);

    std::cout << "Age        : ";
    std::string age_str;
    std::getline(std::cin, age_str);
    // Convert the string input to an integer.
    emp.age = std::atoi(age_str.c_str());

    std::cout << "Gender     : ";
    std::getline(std::cin, emp.gender);

    // 4. Restore Raw Mode (Linux/macOS)
#if !defined(_WIN32) && !defined(_WIN64)
    // Back to raw mode after all buffered input is complete.
    set_raw_mode(true);
#endif

    // 5. Save Employee Data
    employees[count] = emp;
    count++;

    // 6. Pause before returning to menu (requires temporarily switching modes again)
    std::cout << "\nEmployee added. Press ENTER to return to menu...";
    std::cout.flush();

#if defined(_WIN32) || defined(_WIN64)
    // Windows specific buffer ignore/pause.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#else
    // Linux/macOS: Temporarily switch to normal mode for pause input.
    set_raw_mode(false);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    set_raw_mode(true);
#endif
}

/**
 * @brief Displays the list of all recorded employees.
 * @param employees The array of Employee structs.
 * @param count The current number of employees in the array.
 */
void show_employees(const Employee* employees, int count) {
    clear_screen();

    std::cout << "=== Employee List ===\n\n";

    if (count == 0) {
        std::cout << "No employees yet.\n";
    } else {
        // Display details for each employee in a formatted list.
        for (int i = 0; i < count; ++i) {
            std::cout << "Employee #" << (i + 1) << ":\n";
            std::cout << "  First name : " << employees[i].first_name << "\n";
            std::cout << "  Last name  : " << employees[i].last_name  << "\n";
            std::cout << "  Age        : " << employees[i].age        << "\n";
            std::cout << "  Gender     : " << employees[i].gender     << "\n";
            std::cout << "----------------------------------------\n";
        }
    }

    // 7. Wait for user input to return to menu (requires raw mode).
    std::cout << "\nPress BACKSPACE or HOME to return to menu.\n";
    std::cout.flush();

    // Loop blocks until BACKSPACE or HOME key is pressed (input received via raw mode).
    bool in_display = true;
    while (in_display) {
        i32 key = get_key();
        if (key == KEY_BACK || key == KEY_HOME) {
            in_display = false;
        }
    }
}