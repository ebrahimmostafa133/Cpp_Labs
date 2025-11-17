#include "magic_square.h"
#include "custom_datatypes.h"
#include <stdio.h>

int main() {
    // i32 is defined in custom_datatypes.h
    i32 n_input;
    
    printf("Welcome to the Dynamic Magic Square Generator.\n");
    printf("Enter a positive ODD number (N) for the square dimension (e.g., 3, 5, 7, max %d): ", MAX_N);
    
    if (scanf("%d", &n_input) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    // Input validation: Must be positive and odd for this algorithm
    if (n_input <= 0 || n_input % 2 == 0) {
        printf("Error: The Siamese algorithm requires a positive ODD number (N).\n");
        return 1;
    }

    if (n_input > MAX_N) {
        printf("Warning: N is large. Capping at N=%d for smooth visual display.\n", MAX_N);
        n_input = MAX_N; // Capping for display
    }

    // Call the core generation function
    generate_magic_square(n_input);

    return 0;
}