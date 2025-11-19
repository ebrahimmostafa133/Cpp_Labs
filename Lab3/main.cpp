#include "magic.h"
#include "custom_types.h"
#include <stdio.h>

int main() {
    i32 n;

    printf("Magic Square Generator\n");
    printf("Enter ODD N (max %d): ", MAX_N);

    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n <= 0 || n % 2 == 0) {
        printf("Error: N must be positive and ODD.\n");
        return 1;
    }

    if (n > MAX_N) {
        printf("N too big, using %d.\n", MAX_N);
        n = MAX_N;
    }

    generate_magic(n);

    return 0;
}
