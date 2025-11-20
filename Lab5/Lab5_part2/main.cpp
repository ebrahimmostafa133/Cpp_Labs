#include <stdio.h>

#define ROWS 3
#define COLS 4

void print2D(int (*arr)[COLS], int rows, int cols) {
    int i, j;
    printf("Array contents:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}

int main(void) {
    int arr[ROWS][COLS] = {
        {1,  2,  3,  4},
        {5,  6,  7,  8},
        {9, 10, 11, 12}
    };

    print2D(arr, ROWS, COLS);

    return 0;
}
