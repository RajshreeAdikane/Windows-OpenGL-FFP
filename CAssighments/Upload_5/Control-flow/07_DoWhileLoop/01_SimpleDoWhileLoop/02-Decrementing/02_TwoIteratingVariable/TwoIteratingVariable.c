#include<stdio.h>

int main(void)
{
    printf("\n\n");
    printf("Printing 1 to 10 and 10 to 100:\n\n");

    int i = 10, j = 100;
    do {
        printf("\ti = %d \t j = %d\n", i, j);
        i--;
        j -= 10;
    } while (i >= 1 && j >= 10);

    return 0;
}
