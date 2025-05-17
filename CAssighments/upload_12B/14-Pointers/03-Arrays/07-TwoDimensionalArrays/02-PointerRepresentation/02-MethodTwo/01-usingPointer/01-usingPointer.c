#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 5
#define NUM_COL 3

int main(void) {
    int** ptr_arr = NULL;

    ptr_arr = (int**)malloc(NUM_ROWS * sizeof(int*));
    if (ptr_arr == NULL) {
        printf("Memory allocation to the 1D array of base addresses of %d rows failed!!\n\n", NUM_ROWS);
        exit(0);
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        ptr_arr[i] = (int*)malloc(NUM_COL * sizeof(int));
        if (ptr_arr[i] == NULL) {
            printf("Memory allocation to the columns of row %d failed!\n\n", i);
            exit(0);
        }
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COL; j++) {
            *(*(ptr_arr + i) + j) = (i + 1) * (j + 1);
        }
    }

    printf("\n2D Array Elements and Addresses:\n\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COL; j++) {
            printf("ptr_arr[%d][%d] = %d \t Address &ptr_arr[%d][%d] = %p\n",
                i, j, ptr_arr[i][j], i, j, &ptr_arr[i][j]);
        }
    }

    for (int i = (NUM_ROWS - 1); i >= 0; i--) {
        if (ptr_arr[i]) {
            free(ptr_arr[i]);
            ptr_arr[i] = NULL;
            printf("Successfully freed memory allocated to row %d\n\n", i);
        }
    }

    if (ptr_arr) {
        free(ptr_arr);
        ptr_arr = NULL;
        printf("Memory freed allocated to ptr_arr\n\n");
    }

    return 0;
}
