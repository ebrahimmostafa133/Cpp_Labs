#include "console_io.h"
#include "ui_drawing.h"
#include "employee_management.h"


#include <iostream>
#include <limits>
#include <cstdlib> // for std::atoi

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