#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 5
#define NUM_COLS 3

int main(void) {
    int* array[NUM_ROWS]; 

    for (int i = 0; i < NUM_ROWS; i++) {
        array[i] = (int*)malloc(NUM_COLS * sizeof(int));
        if (array[i] == NULL) {
            printf("Failed to allocate memory for row %d.\n", i);
            exit(EXIT_FAILURE);
        }
        else {
            printf("Memory allocation for row %d successful.\n", i);
        }
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
        printf("\n");
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        free(array[i]);
        array[i] = NULL; 
        printf("Memory for row %d successfully freed.\n", i);
    }

    return 0;
}
