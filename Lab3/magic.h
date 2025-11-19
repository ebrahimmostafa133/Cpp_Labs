#ifndef MAGIC_H
#define MAGIC_H

#include "custom_types.h"
#include <stdio.h>

#define DELAY_MS 150
#define MAX_N    19

void delay_ms(u32 ms);
void print_square(i32 n, u32 square[MAX_N][MAX_N]);
void generate_magic(i32 n);

#endif
