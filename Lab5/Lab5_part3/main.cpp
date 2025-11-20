#include <stdio.h>

void swap_xor(int *a, int *b) {
    if (a == b) return;          // same address, do nothing
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void swap_addsub(int *a, int *b) {
    if (a == b) return;
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap_muldiv(int *a, int *b) {
    if (a == b) return;
    if (*a == 0 || *b == 0) return;   // avoid division by zero
    *a = (*a) * (*b);
    *b = (*a) / (*b);
    *a = (*a) / (*b);
}

int main(void) {
    int x = 5, y = 9;

    printf("Original: x=%d y=%d\n", x, y);

    swap_xor(&x, &y);
    printf("After swap_xor: x=%d y=%d\n", x, y);

    swap_addsub(&x, &y);
    printf("After swap_addsub: x=%d y=%d\n", x, y);

    swap_muldiv(&x, &y);
    printf("After swap_muldiv: x=%d y=%d\n", x, y);

    return 0;
}
