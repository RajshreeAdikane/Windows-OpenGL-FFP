#include<stdio.h>

int main(void)
{
    char cArray[10];
    char* ptr_cArray = NULL;
    for (int i = 0; i < 10; i++) {
        cArray[i] = 'A' + i;  
    }
    printf("\n\nChar Array Elements and Addresses:\n\n");

    ptr_cArray = cArray;
    for (int i = 0; i < 10; i++) {
        printf("cArray[%d]=%c \t Address =%p\n", i,*(ptr_cArray+i), (ptr_cArray + i));
    }


    return 0;
}