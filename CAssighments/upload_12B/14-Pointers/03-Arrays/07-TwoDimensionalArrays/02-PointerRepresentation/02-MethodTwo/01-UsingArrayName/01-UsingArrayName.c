#include <stdio.h>

#define NUM_ROWS 5
#define NUM_COL 3

int main(void)
{

    int array[NUM_ROWS][NUM_COL];

    //int (*ptr)[NUM_COL] = array;

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COL; j++) {
            *(*(array +i) + j) = (i + 1) * (j + 1);
        }
    }

    printf("\n2D Array Elements and Addresses:\n\n");
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COL; j++) {
            printf("*(*(array+%d)+%d) = %d =  \t Address = %p\n", i, j, *(*(array + i) + j),(*(array +i) + j));
        }
    }

    return 0;
}
