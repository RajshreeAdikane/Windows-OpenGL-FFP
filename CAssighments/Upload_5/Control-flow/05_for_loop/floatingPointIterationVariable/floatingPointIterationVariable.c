#include <stdio.h>

int main(void)
{
    float RKA_fR;
    float RKA_fA = 12.12f;

    printf("\n\n");
    printf("Printing the numbers %f to %f:\n\n", RKA_fA, (RKA_fA + 10.0f));
    for (RKA_fR = RKA_fA; RKA_fR <= (RKA_fA + 10.0f); RKA_fR += 1.0f)
    {
        printf("\t%f\n", RKA_fR); 
    }

    return 0;
}
