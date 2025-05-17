#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 5
#define NUM_COLS_ONE 3
#define NUM_COLS_TWO 8

int main(void) {
    int* Array[NUM_ROWS];
    for (int i = 0; i < NUM_ROWS; i++) {
        Array[i] = (int*)malloc(NUM_COLS_ONE * sizeof(int));
        if (Array[i] == NULL) {
            printf("Memory allocation failed for row %d in Array.\n", i);
            exit(0);
        }
        else {
            printf("Memory allocation to row %d of 2D int Array success!\n", i);
        }
    }

    printf("\nArray2D (Columns = %d):\n\n", NUM_COLS_ONE);
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS_ONE; j++) {
            Array[i][j] = (i + 1) * (j + 1);
            printf("Array[%d][%d] = %d\n\n", i, j, Array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        free(Array[i]);
        Array[i] = NULL;
        printf("Memory for row %d has been successfully freed.\n", i);
    }

    printf("\n\n");

    for (int i = 0; i < NUM_ROWS; i++) {
        Array[i] = (int*)malloc(NUM_COLS_TWO * sizeof(int));
        if (Array[i] == NULL) {
            printf("Memory allocation failed for row %d in Array.\n", i);
            exit(0);
        }
        else {
            printf("Memory allocation to row %d of 2D int Array success!\n", i);
        }
    }

    printf("\nArray2D (Columns = %d):\n\n", NUM_COLS_TWO);
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS_TWO; j++) {
            Array[i][j] = (i + 1) * (j + 1);
            printf("Array[%d][%d] = %d\n\n", i, j, Array[i][j]);
        }
        printf("\n");
    }

    for (int i = (NUM_ROWS - 1); i >= 0; i--) {
        free(Array[i]);
        Array[i] = NULL;
        printf("Memory for row %d has been successfully freed.\n", i);
    }

    return 0;
}
