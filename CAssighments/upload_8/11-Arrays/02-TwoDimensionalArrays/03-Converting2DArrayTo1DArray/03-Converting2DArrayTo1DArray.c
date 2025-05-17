#include<stdio.h>

#define NUM_ROWS 5
#define NUM_COLOUMS 3

int main(void)
{
    int Array_2D[NUM_ROWS][NUM_COLOUMS];
    int Array_1D[NUM_ROWS * NUM_COLOUMS];
    int num;

    printf("Enter the elements you want to fill in the 2D array:\n\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("For row %d:\n", (i + 1));
        for (int j = 0; j < NUM_COLOUMS; j++) {
            printf("Enter number %d: ", (j + 1));
            scanf("%d", &num);
            Array_2D[i][j] = num;
        }
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLOUMS; j++) {
            Array_1D[(i * NUM_COLOUMS) + j] = Array_2D[i][j];
        }
    }

    printf("\n\n1D Array:\n\n");
    for (int i = 0; i < (NUM_ROWS * NUM_COLOUMS); i++) {
        printf("Array_1D[%d] = %d\n", i, Array_1D[i]);
    }

    return 0;
}
