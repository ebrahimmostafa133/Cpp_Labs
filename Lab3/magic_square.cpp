#include "magic_square.h"
#include <stdlib.h>
#include <unistd.h> // Required for usleep (the delay function)
#include <stdio.h>  // Included via magic_square.h

// Function to handle the requested delay (150ms)
void delay_ms(u32 ms) {
    // usleep takes microseconds (1 ms = 1000 us)
    usleep(ms * 1000);
}

// Function to print the magic square dynamically, updating the grid in place
void print_square(i32 n, u32 **square) {
    
    // ANSI escape code to move the cursor UP by N+2 lines (N lines for the grid,
    // 1 line for the header, 1 line for the footer line)
    // This is the key to refreshing the grid in place.
    // We only execute this AFTER the first print (k=1), so we check if square[0][n/2] == 1
    if (square[0][n/2] != 0) {
        printf("\033[%dA", n + 2); // Move cursor up (N lines + header + footer)
    }

    printf("--- Current Magic Square State (N=%d) ---\n", n);
    
    i32 max_val = n * n;
    i32 width = 0;
    
    // Calculate required print width for alignment
    if (max_val > 0) {
         i32 temp = max_val;
         while (temp > 0) {
            temp /= 10;
            width++;
        }
    } else {
        width = 1;
    }
    width += 1; // Add one space padding (minimum width is 2: '1' + ' ')

    for (i32 i = 0; i < n; i++) {
        printf("  "); // Row Indentation
        for (i32 j = 0; j < n; j++) {
            // Print the number. If 0 (unassigned), print spaces.
            if (square[i][j] == 0) {
                // Print empty spaces for unassigned cells
                for(i32 w=0; w<width; w++) printf(" "); 
            } else {
                // Use field width specifier for alignment
                printf("%*u", width, square[i][j]);
            }
        }
        printf("\n");
    }
    printf("------------------------------------------\n");
    fflush(stdout); // Crucial: Ensures the output buffer is flushed immediately for the update
}


// Generates the magic square using the Siamese method.
void generate_magic_square(i32 n) {
    u32 total_cells = n * n;

    // 1. Allocate and initialize memory for the N x N square (all 0s)
    u32 **square = (u32 **)calloc(n, sizeof(u32 *));
    if (!square) {
        perror("Failed to allocate row pointers");
        return;
    }
    for (i32 i = 0; i < n; i++) {
        square[i] = (u32 *)calloc(n, sizeof(u32));
        if (!square[i]) {
            perror("Failed to allocate columns");
            // Clean up on failure
            for (i32 j = 0; j < i; j++) free(square[j]);
            free(square);
            return;
        }
    }

    // 2. Initial position: 1 in the middle of the top row (0, N/2)
    i32 row = 0;
    i32 col = n / 2;
    i32 next_row, next_col;

    printf("Starting %d x %d Magic Square generation. Watch the numbers fill in...\n", n, n);
    
    // Initial print to establish the grid area
    print_square(n, square);


    // 3. Fill the square from k=1 to N*N
    for (u32 k = 1; k <= total_cells; k++) {
        
        // Place the current number 'k'
        square[row][col] = k;
        
        // Print the current state (this function handles the in-place update)
        print_square(n, square);
        delay_ms(DELAY_MS);

        // --- Determine the next position for (k+1) using standard Siamese logic ---
        
        // Calculate default move: Up-Right (Row--, Col++)
        next_row = row - 1;
        next_col = col + 1;

        // Apply boundary wrapping for the default next position
        i32 wrapped_row = (next_row % n + n) % n;
        i32 wrapped_col = (next_col % n + n) % n;

        // Rule 3 (N-Multiple): If k is a multiple of N (i.e., (k % n == 0)), 
        // the next position must be one cell DOWN from the current position.
        if (k % n == 0) {
            row = (row + 1) % n; // Move Down
            // Column remains the same
        } 
        // Rule 2 (Collision): If the Up-Right position is already occupied, 
        // the next position must be one cell DOWN from the current position.
        else if (square[wrapped_row][wrapped_col] != 0) {
            row = (row + 1) % n; // Move Down
            // Column remains the same
        }
        // Rule 1 (Default): Up-Right 
        else {
            row = wrapped_row;
            col = wrapped_col;
        }
    }
    
    // After the loop, print the final state once more without the cursor manipulation
    printf("\n--- Final Magic Square State (N=%d) ---\n", n);
    i32 max_val_final = n * n;
    i32 width_final = 0;
    if (max_val_final > 0) {
         i32 temp = max_val_final;
         while (temp > 0) {
            temp /= 10;
            width_final++;
        }
    } else {
        width_final = 1;
    }
    width_final += 1;

    for (i32 i = 0; i < n; i++) {
        printf("  "); 
        for (i32 j = 0; j < n; j++) {
            printf("%*u", width_final, square[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------------------\n");


    printf("\n--- Generation Complete! ---\n");
    // Calculate and verify the magic sum: M = N * (N^2 + 1) / 2
    i32 magic_sum = n * (n * n + 1) / 2;
    printf("Final Magic Constant (Sum of rows, cols, diagonals): %d\n", magic_sum);


    // 4. Clean up allocated memory
    for (i32 i = 0; i < n; i++) {
        free(square[i]);
    }
    free(square);
}