#include<stdio.h>

int main(void)
{
    // Float Array
    float fArray[10];
    float* ptr_fArray = NULL; 
    for (int i = 0; i < 10; i++) {
        fArray[i] = (i + 1) * 1.5;
    }

    ptr_fArray = fArray;

    printf("\n\nFloat Array Elements and Addresses:\n\n");
    for (int i = 0; i < 10; i++) {
        printf("fArray[%d]=%.2f \t Address =%p\n", i, *(ptr_fArray + i), (ptr_fArray + i));
    }

    return 0;
}
