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

    printf("The size of the 2D Array is %d\n\n\n\n", Array_size);

    Array_num_rows = Array_size / sizeof(Array[0]);
    Array_num_col = sizeof(Array[0]) / sizeof(Array[0][0]);
    Array_num_ele = Array_num_rows * Array_num_col;

    printf("Number of rows in the array: %d\n\n", Array_num_rows);
    printf("Number of columns in the array: %d\n\n", Array_num_col);
    printf("Number of elements in the array: %d\n\n", Array_num_ele);

    printf("Elements of an array:\n\n");
    printf("Array[0][0] = %d\n\n", Array[0][0]);
    printf("Array[0][1] = %d\n\n", Array[0][1]);
    printf("Array[0][2] = %d\n\n", Array[0][2]);

    printf("Array[1][0] = %d\n\n", Array[1][0]);
    printf("Array[1][1] = %d\n\n", Array[1][1]);
    printf("Array[1][2] = %d\n\n", Array[1][2]);
    
    printf("Array[2][0] = %d\n\n", Array[2][0]);
    printf("Array[2][1] = %d\n\n", Array[2][1]);
    printf("Array[2][2] = %d\n\n", Array[2][2]);
    
    printf("Array[3][0] = %d\n\n", Array[3][0]);
    printf("Array[3][1] = %d\n\n", Array[3][1]);
    printf("Array[3][2] = %d\n\n", Array[3][2]);
 
    printf("Array[4][0] = %d\n\n", Array[4][0]);
    printf("Array[4][1] = %d\n\n", Array[4][1]);
    printf("Array[4][2] = %d\n\n", Array[4][2]);

    return 0;
}
