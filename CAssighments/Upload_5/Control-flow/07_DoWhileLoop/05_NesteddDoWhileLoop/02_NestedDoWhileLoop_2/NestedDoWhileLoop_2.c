#include <stdio.h>

int main(void)
{
    printf("\n\n");

    int i = 1;
    do
    {
        printf("i= %d\n", i);
        printf("----------\n\n");
        int j = 1;
        do
        {
            printf("\tj=%d\n", j);
            j++;
        } while (j <= 5);
        printf("----------\n\n");
        printf("\n");

        int k = 1;
        do
        {
            printf("\tk=%d\n", k);
            printf("\n");
            k++;
        } while (k <= 3);
        i++;
    } while (i <= 10);

    printf("\n\n");
    return 0;
}
