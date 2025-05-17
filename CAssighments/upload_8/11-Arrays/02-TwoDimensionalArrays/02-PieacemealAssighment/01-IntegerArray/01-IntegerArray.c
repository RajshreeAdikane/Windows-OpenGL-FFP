#include <stdio.h>


int main(void)
{
    int Array[5][3];

    int int_Size;
    int Array_size;
    int Array_num_ele, Array_num_rows, Array_num_col;

    printf("\n\n");

    int_Size = sizeof(int);
    Array_size = sizeof(Array);

    printf("The size of the 2D Array is %d\n\n\n\n", Array_size);

    Array_num_rows = Array_size / sizeof(Array[0]);
    Array_num_col = sizeof(Array[0]) / sizeof(Array[0][0]);
    Array_num_ele = Array_num_rows * Array_num_col;

    printf("Number of rows in the array: %d\n\n", Array_num_rows);
    printf("Number of columns in the array: %d\n\n", Array_num_col);
    printf("Number of elements in the array: %d\n\n", Array_num_ele);

    printf("Elements of an array:\n\n");
    Array[0][0] = 1;
    Array[0][1] = 2;
    Array[0][2] = 3;

    Array[1][0] = 4;
    Array[1][1] = 5;
    Array[1][2] = 6;

    Array[2][0] = 7;
    Array[2][1] = 8;
    Array[2][2] = 9;

    Array[3][0] = 10;
    Array[3][1] = 11;
    Array[3][2] = 12;

    Array[4][0] = 13;
    Array[4][1] = 14;
    Array[4][2] = 15;

    for (int i = 0; i < Array_num_rows; i++)
    {
        for (int j = 0; j < Array_num_col; j++) // Fixed condition
        {
            printf("Array[%d][%d] = %d\n", i, j, Array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
