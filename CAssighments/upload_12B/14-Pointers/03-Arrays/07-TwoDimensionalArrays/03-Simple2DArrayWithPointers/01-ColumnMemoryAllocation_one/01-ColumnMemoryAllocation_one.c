#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 5
#define NUM_COLS 3

int main(void) {
    int* array[NUM_ROWS];


    //array = (int**)malloc(NUM_ROWS * sizeof(int*));

    for (int i = 0; i < NUM_ROWS; i++) {
        array[i] = (int*)malloc(NUM_COLS * sizeof(int));
        if (array[i] == NULL) {
            printf("Failed to allocate memory for columns in row %d.\n", i);
            exit(1);
        }
        else
            printf("Memory allocation to row %d of 2D int Array succes\n\n", i);
    }

      for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            array[i][j] = (i + 1) * (j + 1);
        }
    }

    printf("\n2D Array Elements and Addresses:\n\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            printf("array[%d][%d] = %d \t Address = %p\n", i, j, array[i][j], (void*)&array[i][j]);
        }
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}
