#include<stdio.h>

int main(void)
{
    // for loop increment
    printf("\n\n");
    printf("Printing 1 to 10 and 10 to 100:\n\n");
    for (int i = 1, j = 10; i <= 10 && j <= 100; i++, j += 10)
    {
        printf("\ti = %d \t j = %d\n", i, j);
    }
    return 0;
}
