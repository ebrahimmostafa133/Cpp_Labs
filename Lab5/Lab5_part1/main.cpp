#include "./console/console_utils.h"

// Main app loop
i32 main() {
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