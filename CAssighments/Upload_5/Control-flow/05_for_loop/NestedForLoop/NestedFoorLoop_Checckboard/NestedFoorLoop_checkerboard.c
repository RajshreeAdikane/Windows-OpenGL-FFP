#include <stdio.h>

int main(void)
{
    printf("\n\n");

    for (int i = 0; i < 64; i++) 
    {
        for (int j = 0; j < 64; j++) 
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
        }
        printf("\n"); 
    }

    printf("\n\n");
    return 0;
}
