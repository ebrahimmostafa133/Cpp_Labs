#include "console_utils.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

// --- Platform-Specific Includes and Implementations ---

#if defined(_WIN32) || defined(_WIN64)
    // Windows implementation
    #include <conio.h>
    #include <windows.h>
    
    // Windows needs special init/restore if we rely on _getch, 
    // but we need to enable ANSI sequences if possible.
    void init_console() {
        // Attempt to enable ANSI escape codes on Windows 10/11
        // This is necessary for colors and clear_screen to work on modern terminals.
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
    }
    
    void restore_console() {
        // No-op for this simple Windows implementation
    }

    void clear_screen() {
        // Use ANSI escape code to clear screen and move cursor to (0,0)
        std::cout << "\033[2J\033[1;1H" << std::flush;
    }
    
    void gotoXY(i32 x, i32 y) {
        // ANSI escape code for cursor positioning: \033[Row;ColumnH
        std::cout << "\033[" << y << ";" << x << "H" << std::flush;
    }

    TerminalSize get_terminal_size() {
        TerminalSize size = {25, 80}; // Default fallback
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
            size.cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            size.rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
        return size;
    }

    i32 get_key() {
        i32 ch = _getch();

        // Handle ENTER key
        if (ch == '\r') {
            return KEY_ENTER_CUSTOM;
        }
        
        // Handle Backspace key (ASCII 8)
        if (ch == '\b') {
            return KEY_BACKSPACE_CUSTOM;
        }

        // Handle special keys (arrows) - they usually come as two keys in Windows: 0 or 0xE0, followed by the actual key code
        if (ch == 0 || ch == 0xE0) {
            ch = _getch(); // Read the second byte (the scan code)
            switch (ch) {
                case 72: return KEY_UP_CUSTOM;    // Up arrow scan code
                case 80: return KEY_DOWN_CUSTOM;  // Down arrow scan code
                default: return 0; // Unhandled special key
            }
        }

        return ch;
    }

#else
    // POSIX (Linux, macOS) implementation using termios
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h> // For ioctl/TIOCGWINSZ
    
    static struct termios original_termios;

    void init_console() {
        struct termios new_termios;
        tcgetattr(STDIN_FILENO, &original_termios);
        new_termios = original_termios;
        
        // Disable canonical mode (line buffering) and echo
        new_termios.c_lflag &= ~(ICANON | ECHO); 
        // Set VMIN=1 (minimum one character read) and VTIME=0 (no timeout)
        new_termios.c_cc[VMIN] = 1;
        new_termios.c_cc[VTIME] = 0;
        
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    }
    
    void restore_console() {
        tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    }

    void clear_screen() {
        // Use standard ANSI escape code to clear screen and move cursor to (0,0)
        std::cout << "\033[2J\033[1;1H" << std::flush;
    }

    void gotoXY(i32 x, i32 y) {
        // ANSI escape code for cursor positioning: \033[Row;ColumnH
        // Flush immediately to ensure cursor moves before next output
        std::cout << "\033[" << y << ";" << x << "H" << std::flush;
    }

    TerminalSize get_terminal_size() {
        TerminalSize size = {25, 80}; // Default fallback
        struct winsize ws;
        
        // TIOCGWINSZ gets the terminal window size
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) != -1) {
            size.rows = ws.ws_row;
            size.cols = ws.ws_col;
        }
        return size;
    }

    i32 get_key() {
        i32 ch = getchar(); // Read the first character

        // Handle arrow keys - they often start with an escape sequence (0x1B)
        if (ch == 0x1B) { 
            // Set termios to non-blocking read (VMIN=0) for sequence check
            struct termios current_termios;
            tcgetattr(STDIN_FILENO, &current_termios);
            struct termios temp_termios = current_termios;
            temp_termios.c_cc[VMIN] = 0;
            tcsetattr(STDIN_FILENO, TCSANOW, &temp_termios);
            
            // Read next two characters of the sequence: [ and A/B/C/D
            i32 seq1 = getchar();
            i32 seq2 = getchar();

            // Restore VMIN to blocking read
            tcsetattr(STDIN_FILENO, TCSANOW, &current_termios);

            if (seq1 == 0x5B) { // Check for '[' (CSI)
                if (seq2 == 'A') return KEY_UP_CUSTOM;    // ESC [ A
                if (seq2 == 'B') return KEY_DOWN_CUSTOM;  // ESC [ B
            }
            return 0; // Unhandled ESC sequence
        }
        
        // Handle Enter (Newline)
        if (ch == '\n' || ch == '\r') {
            return KEY_ENTER_CUSTOM;
        }

        // Handle Backspace (usually ASCII 127 or 8)
        if (ch == 127 || ch == 8) {
            return KEY_BACKSPACE_CUSTOM;
        }

        return ch;
    }
#endif // _WIN32