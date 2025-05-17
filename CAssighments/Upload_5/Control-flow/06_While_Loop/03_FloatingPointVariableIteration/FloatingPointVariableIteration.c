#include <stdio.h>

int main(void)
{
    float RKA_fR;             
    float RKA_fA = 1.23f;    

    printf("\n\n");
    printf("Printing the numbers %f to %f:\n\n", RKA_fA, (RKA_fA + 10.0f));

    RKA_fR = RKA_fA;           
    while (RKA_fR <= (RKA_fA + 10.0f)) 
    {
        printf("\t%f\n", RKA_fR);
        RKA_fR += 1.0f;       
    }

    return 0;
}
