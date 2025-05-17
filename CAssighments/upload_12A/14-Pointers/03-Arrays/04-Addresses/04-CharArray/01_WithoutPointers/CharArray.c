#include<stdio.h>

int main(void)
{
    char cArray[10];
    for (int i = 0; i < 10; i++) {
        cArray[i] = 'A' + i;  // Assign letters A-J
    }
    printf("\n\nChar Array Elements and Addresses:\n\n");
    for (int i = 0; i < 10; i++) {
        printf("cArray[%d]=%c \t Address =%p\n", i, cArray[i], &cArray[i]);
    }



    return 0;
}