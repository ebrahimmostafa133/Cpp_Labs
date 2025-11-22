#include "console_utils.h"

#include <cstdio>
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
