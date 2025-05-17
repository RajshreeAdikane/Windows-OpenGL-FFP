#include<stdio.h>

int main(void)
{
    int a;
    int* ptr = NULL;
    int** pptr = NULL; 

    a = 9;
    printf("\n\n");
    printf("***** BEFORE ptr = &a *****\n");
    printf("a = %d\n", a);
    printf("&a = %p\n", &a);
    printf("*(&a) = %d\n", *(&a));



    ptr = &a;

    printf("\n***** AFTER ptr = &a *****\n");
    printf("a = %d\n", a);
    //printf("&a = %p\n", &a);
    //printf("*(&a) = %d\n", *(&a));
    printf("*ptr = %d\n", *ptr); 
    printf("ptr = %p\n", ptr);

    pptr = &ptr;
    printf("\n***** AFTER pptr =&ptr  *****\n");
    printf("a = %d\n", a);
    printf("ptr = %p\n", ptr);
    printf("pptr = %p\n", pptr);
    printf("*pptr = %p\n", *pptr);  
    printf("**pptr = %d\n", **pptr);  
    return 0;
}
