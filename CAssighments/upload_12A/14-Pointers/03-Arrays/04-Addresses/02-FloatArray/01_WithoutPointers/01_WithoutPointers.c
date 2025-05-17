#include<stdio.h>

int main(void)
{
    // Float Array
    float fArray[10];
    for (int i = 0; i < 10; i++) {
        fArray[i] = (i + 1) * 1.5;
    }
    printf("\n\nFloat Array Elements and Addresses:\n\n");
    for (int i = 0; i < 10; i++) {
        printf("fArray[%d]=%.2f \t Address =%p\n", i, fArray[i], &fArray[i]);
    }

    return 0;
}