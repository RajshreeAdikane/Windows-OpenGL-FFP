#include<stdio.h>

int main(void)
{
    int iArray[] = { 3,6,9,12,15,18,21,24,27,30 };
    int* ptr_array = NULL;

    printf("\n\n");
    printf("Array elements and Address\n");
    printf("iArray[0] = %d \t Address:%p\n", *(iArray + 0), (iArray + 0));
    printf("iArray[1] = %d \t Address:%p\n", *(iArray + 1), (iArray + 1));
    printf("iArray[2] = %d \t Address:%p\n", *(iArray + 2), (iArray + 2));
    printf("iArray[3] = %d \t Address:%p\n", *(iArray + 3), (iArray + 3));
    printf("iArray[4] = %d \t Address:%p\n", *(iArray + 4), (iArray + 4));
    printf("iArray[5] = %d \t Address:%p\n", *(iArray + 5), (iArray + 5));
    printf("iArray[6] = %d \t Address:%p\n", *(iArray + 6), (iArray + 6));
    printf("iArray[7] = %d \t Address:%p\n", *(iArray + 7), (iArray + 7));
    printf("iArray[8] = %d \t Address:%p\n", *(iArray + 8), (iArray + 8));
    printf("iArray[9] = %d \t Address:%p\n", *(iArray + 9), (iArray + 9));


    ptr_array = iArray;  // Set ptr_array to point to the start of iArray
    printf("\nUsing Pointers: Array elements and Address\n");
    printf("ptr_array[0] = %d \t Address:%p\n", ptr_array[0], &ptr_array[0]);
    printf("ptr_array[1] = %d \t Address:%p\n", ptr_array[1], &ptr_array[1]);
    printf("ptr_array[2] = %d \t Address:%p\n", ptr_array[2], &ptr_array[2]);
    printf("ptr_array[3] = %d \t Address:%p\n", ptr_array[3], &ptr_array[3]);
    printf("ptr_array[4] = %d \t Address:%p\n", ptr_array[4], &ptr_array[4]);
    printf("ptr_array[5] = %d \t Address:%p\n", ptr_array[5], &ptr_array[5]);
    printf("ptr_array[6] = %d \t Address:%p\n", ptr_array[6], &ptr_array[6]);
    printf("ptr_array[7] = %d \t Address:%p\n", ptr_array[7], &ptr_array[7]);
    printf("ptr_array[8] = %d \t Address:%p\n", ptr_array[8], &ptr_array[8]);
    printf("ptr_array[9] = %d \t Address:%p\n", ptr_array[9], &ptr_array[9]);

    return 0;
}
