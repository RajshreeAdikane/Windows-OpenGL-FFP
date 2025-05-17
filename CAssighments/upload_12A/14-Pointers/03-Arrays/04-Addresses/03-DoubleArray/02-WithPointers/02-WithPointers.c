#include<stdio.h>

int main(void)
{
    double dArray[10];
    double* ptr_dArray = NULL;

    for (int i = 0; i < 10; i++) {
        dArray[i] = (i + 1) * 2.5;
    }
    printf("\n\nDouble Array Elements and Addresses:\n\n");

    ptr_dArray = dArray;
    for (int i = 0; i < 10; i++) {
        printf("dArray[%d]=%.2f \t Address =%p\n", i, *(ptr_dArray+i), (ptr_dArray + i));
    }


    return 0;
}