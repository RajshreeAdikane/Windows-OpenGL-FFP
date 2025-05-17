#include <stdio.h>


int main(void)
{
    int Array[5][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}, {13, 14, 15} };

    int int_Size;
    int Array_size;
    int Array_num_ele, Array_num_rows, Array_num_col;

    printf("\n\n");

    int_Size = sizeof(int);
    Array_size = sizeof(Array);

    printf("The size of the 2D Array is %d\n\n", Array_size);

    Array_num_rows = Array_size / sizeof(Array[0]);
    Array_num_col = sizeof(Array[0]) / sizeof(Array[0][0]);
    Array_num_ele = Array_num_rows * Array_num_col;

    printf("Number of rows in the array: %d\n", Array_num_rows);
    printf("Number of columns in the array: %d\n", Array_num_col);
    printf("Number of elements in the array: %d\n\n", Array_num_ele);

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
