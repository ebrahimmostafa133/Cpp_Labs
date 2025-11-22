#ifndef EMPLOYEE_MANAGEMENT_H
#define EMPLOYEE_MANAGEMENT_H

#include "custom_types.h"
#include <string>

// Simple employee struct
typedef struct {
    std::string first_name;
    std::string last_name;
    int         age;
    std::string gender;
} Employee;

// Employee screens
void add_employee(Employee* employees, int& count, int max_count);
void show_employees(const Employee* employees, int count);

#endif // EMPLOYEE_MANAGEMENT_H