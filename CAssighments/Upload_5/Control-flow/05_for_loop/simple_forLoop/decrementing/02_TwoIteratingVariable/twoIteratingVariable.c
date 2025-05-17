#include<stdio.h>

int main(void)
{
    // for loop decrementing
    printf("\n\n");
    printf("Printing 10 to 11 and 100 to 10:\n\n");
    for (int i = 10, j = 100; i >= 1 && j >= 10; i--, j -= 10)
    {
        printf("\ti = %d \t j = %d\n", i, j);
    }
    return 0;
}
