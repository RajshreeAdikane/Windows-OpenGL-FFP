#include <stdio.h>

int main(void)
{
    printf("\n\n");

    int i = 0;
    while (i < 64)
    {
        int j = 0;
        while (j < 64)
        {
            int c;
            c = ((i / 8) ^ (j / 8)) & 1;

            if (c == 0)
            {
                printf("  ");
            }
            else
            {
                printf("* ");
            }
            j++;
        }
        printf("\n");
        i++;
    }

    printf("\n\n");
    return 0;
}
