#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int rows, cols;
    int** array;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL) {
        printf("Failed to allocate memory for rows.\n");
        exit(0);
    }

    for (int i = 0; i < rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
        if (array[i] == NULL) {
            printf("Failed to allocate memory for columns in row %d.\n", i);
            exit(0);
        }
    }

    printf("\nEnter the elements of the 2D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter value for array[%d][%d]: ", i, j);
            scanf("%d", &array[i][j]);
        }
    }

    printf("\n2D Array Elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(array[i]); 
        array[i] = NULL; 
    }
    free(array); 
    array = NULL;

    printf("\nMemory successfully freed.\n");
    return 0;
}
