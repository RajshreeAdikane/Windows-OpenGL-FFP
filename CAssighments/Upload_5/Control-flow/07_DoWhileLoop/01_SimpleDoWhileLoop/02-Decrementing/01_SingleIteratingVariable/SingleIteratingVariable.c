#include<stdio.h>

int main(void)
{
    printf("\n\n");
    printf("printing 1 to 10: \n\n");

    int i = 10;
    do {
        printf("%d\n", i);
        i--;
    } while (i >= 1);

    return(0);
}
