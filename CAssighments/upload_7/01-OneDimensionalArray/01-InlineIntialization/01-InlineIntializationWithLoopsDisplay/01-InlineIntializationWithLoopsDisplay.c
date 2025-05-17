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
    printf("Peace-meal and inline initialization of integer array:\n");
    printf("Array_1[0] = %d\n", Array_1[0]);
    printf("Array_1[1] = %d\n", Array_1[1]);
    printf("Array_1[2] = %d\n", Array_1[2]);

    A_size = sizeof(int);
    Array_1_size = sizeof(Array_1);
    Array_num_ele = Array_1_size / A_size;

    printf("The size of an integer in bytes = %d\n", A_size);
    printf("Number of elements in the integer array = %d\n", Array_num_ele);
    printf("Size of the integer array in bytes = %d\n\n", Array_1_size);

    // Float Array
    printf("Peace-meal and inline initialization of float array:\n");
    printf("Array_f[0] = %.2f\n", Array_f[0]);
    printf("Array_f[1] = %.2f\n", Array_f[1]);
    printf("Array_f[2] = %.2f\n", Array_f[2]);
    printf("Array_f[3] = %.2f\n", Array_f[3]);

    Array_f_size = sizeof(float);
    Array_f_fsize = sizeof(Array_f);
    Array_f_num_ele = Array_f_fsize / Array_f_size;

    printf("The size of a float in bytes = %d\n", Array_f_size);
    printf("Number of elements in the float array = %d\n", Array_f_num_ele);
    printf("Size of the float array in bytes = %d\n\n", Array_f_fsize);

    // Char Array
    printf("Peace-meal and inline initialization of char array:\n");
    printf("Array_c[0] = %c\n", Array_c[0]);
    printf("Array_c[1] = %c\n", Array_c[1]);
    printf("Array_c[2] = %c\n", Array_c[2]);
    printf("Array_c[3] = %c\n", Array_c[3]);
    printf("Array_c[4] = %c\n", Array_c[4]);
    printf("Array_c[5] = %c\n", Array_c[5]);
    printf("Array_c[6] = %c\n", Array_c[6]);
    printf("Array_c[7] = %c\n", Array_c[7]);
    printf("Array_c[8] = %c\n", Array_c[8]);

    Array_c_size = sizeof(char);
    Array_c_csize = sizeof(Array_c);
    Array_c_num_ele = Array_c_csize / Array_c_size;

    printf("The size of a char in bytes = %d\n", Array_c_size);
    printf("Number of elements in the char array = %d\n", Array_c_num_ele);
    printf("Size of the char array in bytes = %d\n\n", Array_c_csize);

    return 0;
}
