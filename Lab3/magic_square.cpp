#include "magic.h"
#include "custom_types.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void delay_ms(u32 ms) {
    usleep(ms * 1000);
}

void print_square(i32 n, u32 square[MAX_N][MAX_N]) {
    if (n > 0 && square[0][n / 2] != 0) {
        printf("\033[%dA", n + 2);
    }

    printf("--- Magic Square N=%d ---\n", n);

    i32 max_val = n * n;
    i32 width = 0;

    if (max_val > 0) {
        i32 temp = max_val;
        while (temp > 0) {
            temp /= 10;
            width++;
        }
    } else {
        width = 1;
    }
    width += 1;

    for (i32 i = 0; i < n; i++) {
        printf("  ");
        for (i32 j = 0; j < n; j++) {
            if (square[i][j] == 0) {
                for (i32 w = 0; w < width; w++) printf(" ");
            } else {
                printf("%*u", width, square[i][j]);
            }
        }
        printf("\n");
    }
    printf("-------------------------\n");
    fflush(stdout);
}

void generate_magic(i32 n) {
    if (n > MAX_N) {
        n = MAX_N;
    }

    u32 square[MAX_N][MAX_N];

    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j < n; j++) {
            square[i][j] = 0;
        }
    }

    i32 row = 0;
    i32 col = n / 2;
    i32 next_row, next_col;
    u32 total_cells = n * n;

    printf("Starting %d x %d magic square...\n", n, n);
    print_square(n, square);

    for (u32 k = 1; k <= total_cells; k++) {
        square[row][col] = k;
        print_square(n, square);
        delay_ms(DELAY_MS);

        next_row = row - 1;
        next_col = col + 1;

        i32 wrapped_row = (next_row % n + n) % n;
        i32 wrapped_col = (next_col % n + n) % n;

        if (k % n == 0) {
            row = (row + 1) % n;
        } else if (square[wrapped_row][wrapped_col] != 0) {
            row = (row + 1) % n;
        } else {
            row = wrapped_row;
            col = wrapped_col;
        }
    }

    printf("\n--- Done ---\n");
    i32 magic_sum = n * (n * n + 1) / 2;
    printf("Magic sum: %d\n", magic_sum);
}
