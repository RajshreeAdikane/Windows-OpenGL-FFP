#include<stdio.h>

int main(void)
{
    int i, j;
    printf("\n\n");

    for (i = 1; i <= 10; i++)  // Initialize i correctly
    {
        if (i % 2 != 0)
        {
            printf("\tThese are odd numbers i=%d", i);
            printf("______\n");

            for (j = 1; j <= 10; j++)
            {
                if (j % 2 == 0)
                {
                    printf("\tThese are even numbers j=%d", j);
                }
                else
                {
                    continue;
                }
            }
            printf("\n\n");
        }
        else
        {
            continue;
        }
    }
    return(0);
}
