#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#include "custom_datatypes.h"
#include <stdio.h> // For size_t and basic types used in prototypes

// --- Constants ---
#define DELAY_MS 150 // The requested delay in milliseconds
#define MAX_N 19     // Upper limit for practical console demonstration

/**
 * @brief Pauses execution for the specified number of milliseconds.
 * @param ms The time in milliseconds to pause.
 */
void delay_ms(u32 ms);

/**
 * @brief Prints the current state of the N x N magic square.
 * @param n The dimension of the square.
 * @param square A pointer to the 2D array of the square data.
 */
void print_square(i32 n, u32 **square);

/**
 * @brief Generates and prints the magic square using the Siamese method.
 * @param n The odd dimension of the square (N x N).
 */
void generate_magic_square(i32 n);

#endif // MAGIC_SQUARE_H