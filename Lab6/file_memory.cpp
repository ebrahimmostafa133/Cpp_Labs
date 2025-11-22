#include "console_utils.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm> 

void* allocate_memory(u32 size) {
    void* ptr = std::malloc(size);
    if (ptr == nullptr) {
        std::cerr << "Error: Failed to allocate " << size << " bytes.\n";
    }
    return ptr;
}

void free_memory(void* ptr) {
    if (ptr != nullptr) {
        std::free(ptr);
    }
}

i32 save_overwrite(const char* name, const char* data, i32 size) {
    std::ofstream file(name, std::ios::trunc);
    if (file.is_open()) {
        file.write(data, size);
        file.close();
        return 0;
    } else {
        std::cerr << "Error: Could not open file for writing: " << name << "\n";
        return -1;
    }
}

i32 save_append(const char* name, const char* data, i32 size) {
    std::ofstream file(name, std::ios::app);
    if (file.is_open()) {
        file.write(data, size);
        file.close();
        return 0;
    } else {
        std::cerr << "Error: Could not open file for appending: " << name << "\n";
        return -1;
    }
}

std::string read_file(const char* name) {
    std::ifstream file(name);
    if (file.is_open()) {
        std::string content((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
        file.close();
        return content;
    } else {
        return ""; 
    }
}
