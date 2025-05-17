#include<stdio.h>

int main(void)
{
    // Character arrays
    char My_Array[] = { 'R', 'A', 'j', 'A', 'S', 'H', 'R', 'E', 'E', '\0' };
    char i_Array[] = "Roll no is 20";
    char j_Array[] = { '2', '0', '2', '4', 'b', 'a', 't', 'c', 'h' }; 

    printf("\n\n");

    // Printing sizes of the arrays
    printf("Size of array 1 is: %zu bytes\n\n", sizeof(My_Array));
    printf("Size of array 2 is: %zu bytes\n\n", sizeof(i_Array));
    printf("Size of array 3 is: %zu bytes\n\n", sizeof(j_Array));

    printf("array 1 is: %s bytes\n\n", My_Array);
    printf("array 2 is: %s bytes\n\n", i_Array);
    printf("array 3 is: %s bytes\n\n", j_Array);

    printf("\n\n");
    return 0;
}
