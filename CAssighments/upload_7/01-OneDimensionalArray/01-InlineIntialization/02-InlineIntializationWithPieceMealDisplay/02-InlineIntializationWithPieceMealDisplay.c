#include <stdio.h>

int main(void)
{
    // Declare arrays properly with correct syntax and sizes
    int Array_1[] = { 2, 5, 6 };
    int A_size;
    int Array_1_size;
    int Array_num_ele;

    float Array_f[] = { 1.2f, 4.6f, 7.4f, 8.9f };
    int Array_f_size;
    int Array_f_fsize;
    int Array_f_num_ele;

    char Array_c[] = { 'R', 'A', 'J', 'A', 'S', 'H', 'R', 'E', 'E' };
    int Array_c_size;
    int Array_c_csize;
    int Array_c_num_ele;

    printf("\n\n");

    // Integer Array
    printf("Loop initialization and inline initialization of integer array:\n");

    A_size = sizeof(int);
    Array_1_size = sizeof(Array_1);
    Array_num_ele = Array_1_size / A_size;

    for (int i = 0; i < Array_num_ele; i++)
    {
        printf("Integer Array[%d] (Element %d) = %d\n", i, (i + 1), Array_1[i]);
    }

    printf("The size of an integer in bytes = %d\n", A_size);
    printf("Number of elements in the integer array = %d\n", Array_num_ele);
    printf("Size of the integer array in bytes = %d\n\n", Array_1_size);

    // Float Array
    printf("Loop initialization and inline initialization of float array:\n");

    Array_f_size = sizeof(float);
    Array_f_fsize = sizeof(Array_f);
    Array_f_num_ele = Array_f_fsize / Array_f_size;

    for (int i = 0; i < Array_f_num_ele; i++)
    {
        printf("Float Array[%d] (Element %d) = %.2f\n", i, (i + 1), Array_f[i]);
    }

    printf("The size of a float in bytes = %d\n", Array_f_size);
    printf("Number of elements in the float array = %d\n", Array_f_num_ele);
    printf("Size of the float array in bytes = %d\n\n", Array_f_fsize);

    // Char Array
    printf("Loop initialization and inline initialization of char array:\n");

    Array_c_size = sizeof(char);
    Array_c_csize = sizeof(Array_c);
    Array_c_num_ele = Array_c_csize / Array_c_size;

    for (int i = 0; i < Array_c_num_ele; i++)
    {
        printf("Char Array[%d] (Element %d) = %c\n", i, (i + 1), Array_c[i]);
    }

    printf("The size of a char in bytes = %d\n", Array_c_size);
    printf("Number of elements in the char array = %d\n", Array_c_num_ele);
    printf("Size of the char array in bytes = %d\n\n", Array_c_csize);

    return 0;
}
