#include <stdio.h>

int main(void)
{
    printf("\n\n");

    int i = 1; 
    while (i <= 10) 
    {
        printf("i= %d\n", i);
        printf("----------\n\n");
        int j = 1; 
        while (j <= 5) 
        {
            printf("\tj=%d\n", j);
            j++; 
        }
        printf("----------\n\n");
        printf("\n");

        int k = 1; 
        while (k <= 3) 
        {
            printf("\tk=%d\n", k);
            printf("\n");
            k++; 
        }
        i++;
    }

    printf("\n\n");
    return 0;
}
