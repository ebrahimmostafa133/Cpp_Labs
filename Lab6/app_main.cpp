#include "console_utils.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

i32 run_app() {
    const char* menu_items[] = {"New", "Display", "Exit"};
    i32  choice      = 0;
    i32  mode     = MODE_MENU;
    bool running  = true;

    start_console();

    char* buffer = nullptr; 
    i32 current_size = 0;
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
            if (buffer != nullptr) {
                draw_editor(buffer, current_size, max_size, cursor_pos);
            } else {
                mode = MODE_GET_SIZE;
                continue;
            }
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
                    if (buffer != nullptr) {
                        free_memory(buffer);
                        buffer = nullptr;
                        current_size = 0;
                    }
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
                        
                        buffer = (char*)allocate_memory(max_size + 1);
                        if (buffer == nullptr) {
                            max_size = 0;
                            size_input.clear();
                            continue;
                        }
                        buffer[0] = '\0';

                        std::string loaded_data = read_file(FILE_NAME);
                        
                        if (!loaded_data.empty() && (i32)loaded_data.size() <= max_size) {
                             std::strncpy(buffer, loaded_data.c_str(), max_size);
                             buffer[max_size] = '\0';
                             current_size = (i32)loaded_data.size();
                        } else {
                            current_size = 0;
                        }
                        
                        cursor_pos = current_size;
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
                cursor_pos = std::max((i32)0, cursor_pos - 1);
            } else if (key == KEY_RIGHT) {
                cursor_pos = std::min(current_size, cursor_pos + 1);
            } else if (key == KEY_BACK) {
                if (cursor_pos > 0) {
                    std::memmove(buffer + cursor_pos - 1, buffer + cursor_pos, current_size - cursor_pos);
                    current_size--;
                    buffer[current_size] = '\0';
                    cursor_pos = std::max((i32)0, cursor_pos - 1);
                }
            } else if (key == KEY_HOME) {
                choice = 0;
                mode = MODE_FILE_OPTIONS;
            } else if (key >= 32 && key <= 126) {
                if (current_size < max_size) {
                    std::memmove(buffer + cursor_pos + 1, buffer + cursor_pos, current_size - cursor_pos);
                    buffer[cursor_pos] = (char)key;
                    current_size++;
                    buffer[current_size] = '\0';
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
                    save_overwrite(FILE_NAME, buffer, current_size); 
                    mode = MODE_MENU;
                } else if (choice == 1) {
                    save_append(FILE_NAME, buffer, current_size); 
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
    std::cout << "Goodbye! The final buffer was: [";
    if (buffer != nullptr) {
        for (i32 i = 0; i < current_size; ++i) {
            std::cout << buffer[i];
        }
        free_memory(buffer);
    }
    std::cout << "]\n";
    return 0;
}
