#include<stdio.h>

int main(void)
{
    double dArray[10];
    for (int i = 0; i < 10; i++) {
        dArray[i] = (i + 1) * 2.5;
    }
    printf("\n\nDouble Array Elements and Addresses:\n\n");
    for (int i = 0; i < 10; i++) {
        printf("dArray[%d]=%.2f \t Address =%p\n", i, dArray[i], &dArray[i]);
    }


    return 0;
}