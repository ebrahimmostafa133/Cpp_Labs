#include "console_utils.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm> 

#include <termios.h>
#include <unistd.h>

static struct termios old_term;

void start_console() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &old_term);
    t = old_term;

    t.c_lflag &= ~(ICANON | ECHO);
    t.c_cc[VMIN]  = 1;
    t.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void stop_console() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

i32 get_key() {
    int key = getchar();

    if (key == 0x1B) {
        int seq1 = getchar();
        if (seq1 == '[') {
            int seq2 = getchar();
            if (seq2 == 'A') return KEY_UP;
            if (seq2 == 'B') return KEY_DOWN;
            if (seq2 == 'C') return KEY_RIGHT; 
            if (seq2 == 'D') return KEY_LEFT;  
            if (seq2 == 'H') return KEY_HOME;

            if (seq2 == '1') {
                int seq3 = getchar();
                if (seq3 == '~') return KEY_HOME;
            }
        }
        return KEY_OTHER;
    }

    if (key == '\n' || key == '\r') return KEY_ENTER;
    if (key == 127 || key == 8)     return KEY_BACK;

    return key;
}


void clear_screen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void go_xy(i32 x, i32 y) {
    std::cout << "\033[" << y << ";" << x << "H" << std::flush;
}

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

i32 save_overwrite(const char* name, const std::string& data) {
    std::ofstream file(name, std::ios::trunc);
    if (file.is_open()) {
        file << data;
        file.close();
        return 0;
    } else {
        std::cerr << "Error: Could not open file for writing: " << name << "\n";
        return -1;
    }
}

i32 save_append(const char* name, const std::string& data) {
    std::ofstream file(name, std::ios::app);
    if (file.is_open()) {
        file << data;
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
    std::cout << "Buffer: [" << buffer << "]\n";
    
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

i32 run_app() {
    const char* menu_items[] = {"New", "Display", "Exit"};
    i32  choice      = 0;
    i32  mode     = MODE_MENU;
    bool running  = true;

    start_console();

    std::string buffer; 
    std::string file_content;
    
    i32 max_size = 0;
    i32 cursor_pos = 0;
    std::string size_input; 

    while (running) {
        if (mode == MODE_MENU) {
            draw_menu(menu_items, MENU_COUNT, choice);
        } else if (mode == MODE_GET_SIZE) {
            draw_size_prompt();
            go_xy(5 + 33, 6);
            std::cout << size_input << std::flush;
        } else if (mode == MODE_EDIT_STRING) {
            draw_editor(buffer.c_str(), (i32)buffer.size(), max_size, cursor_pos);
        } else if (mode == MODE_FILE_OPTIONS) {
             draw_save_menu(choice);
        } else {
            show_content(file_content.c_str()); 
        }

        i32 key = get_key();

        if (mode == MODE_MENU) {
            if (key == KEY_UP) {
                choice = (choice - 1 + MENU_COUNT) % MENU_COUNT;
            } else if (key == KEY_DOWN) {
                choice = (choice + 1) % MENU_COUNT;
            } else if (key == KEY_ENTER) {
                if (choice == 0) {
                    max_size = 0;
                    size_input.clear();
                    mode = MODE_GET_SIZE;
                } else if (choice == 1) {
                    file_content = read_file(FILE_NAME);
                    mode = MODE_CONTENT;
                } else if (choice == 2) {
                    running = false; 
                }
            }
        } 
        
        else if (mode == MODE_GET_SIZE) {
            if (key >= '0' && key <= '9' && size_input.size() < 4) {
                size_input += (char)key;
            } else if (key == KEY_BACK) {
                if (!size_input.empty()) {
                    size_input.pop_back();
                }
            } else if (key == KEY_ENTER) {
                try {
                    i32 new_size = std::stoi(size_input);
                    if (new_size > 0) {
                        max_size = new_size;
                        
                        std::string loaded_data = read_file(FILE_NAME);
                        
                        if (!loaded_data.empty() && (i32)loaded_data.size() <= max_size) {
                             buffer = loaded_data;
                        } else {
                            buffer.clear();
                        }
                        
                        cursor_pos = (i32)buffer.size();
                        mode = MODE_EDIT_STRING;
                    } else {
                         size_input.clear();
                    }
                } catch (...) {
                    size_input.clear();
                }
            }
        }

        else if (mode == MODE_EDIT_STRING) {
            if (key == KEY_LEFT) {
                cursor_pos = std::max(0, cursor_pos - 1);
            } else if (key == KEY_RIGHT) {
                cursor_pos = std::min((i32)buffer.size(), cursor_pos + 1);
            } else if (key == KEY_BACK) {
                if (cursor_pos > 0) {
                    buffer.erase(cursor_pos - 1, 1);
                    cursor_pos = std::max(0, cursor_pos - 1);
                }
            } else if (key == KEY_HOME) {
                choice = 0;
                mode = MODE_FILE_OPTIONS;
            } else if (key >= 32 && key <= 126) {
                if ((i32)buffer.size() < max_size) {
                    buffer.insert(cursor_pos, 1, (char)key);
                    cursor_pos++;
                }
            }
        }
        
        else if (mode == MODE_FILE_OPTIONS) {
            if (key == KEY_UP) {
                choice = (choice - 1 + FILE_MENU_COUNT) % FILE_MENU_COUNT;
            } else if (key == KEY_DOWN) {
                choice = (choice + 1) % FILE_MENU_COUNT;
            } else if (key == KEY_ENTER) {
                if (choice == 0) {
                    save_overwrite(FILE_NAME, buffer); 
                    mode = MODE_MENU;
                } else if (choice == 1) {
                    save_append(FILE_NAME, buffer); 
                    mode = MODE_MENU;
                } else if (choice == 2) {
                    mode = MODE_EDIT_STRING;
                }
            }
        }
        
        else if (mode == MODE_CONTENT) {
            if (key == KEY_BACK || key == KEY_HOME) {
                mode = MODE_MENU;
            }
        }
    }

    stop_console();
    clear_screen();
    std::cout << "Goodbye! The final buffer was: [" << buffer << "]\n";
    return 0;
}