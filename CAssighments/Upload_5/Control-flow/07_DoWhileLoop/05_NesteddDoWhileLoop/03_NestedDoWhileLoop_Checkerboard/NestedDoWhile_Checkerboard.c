#include <stdio.h>

int main(void)
{
    printf("\n\n");

    int i = 0;
    do
    {
        int j = 0;
        do
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
        } while (j < 64);
        printf("\n");
        i++;
    } while (i < 64);

    printf("\n\n");
    return 0;
}
