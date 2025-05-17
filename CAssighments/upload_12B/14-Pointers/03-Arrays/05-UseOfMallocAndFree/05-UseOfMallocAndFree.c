#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* ptr_Arr = NULL; // Initialize pointer to NULL to avoid garbage values
    unsigned int intArrLength = 0;

    printf("\n\n");
    printf("Enter the number of elements in the array: ");
    scanf("%d", &intArrLength);

    // Allocate memory for the array
    ptr_Arr = (int*)malloc(sizeof(int) * intArrLength);
    if (ptr_Arr == NULL) // Check for successful memory allocation
    {
        printf("\n\nMemory allocation failed!\n\n");
        return -1;
    }
    else
    {
        printf("\n\n");
        printf("Memory allocated successfully!\n");
        printf("Memory address from %p to %p have been allocated to the integer array\n\n",
            ptr_Arr, (ptr_Arr + (intArrLength - 1)));
    }

    printf("\n\n");
    printf("Enter %d elements for the integer array:\n", intArrLength);
    for (int i = 0; i < intArrLength; i++)
    {
        scanf("%d", (ptr_Arr + i)); 
    }

    printf("\n\n");
    printf("The integer array entered is:\n\n");
    for (int i = 0; i < intArrLength; i++)
    {
        printf("ptr_Arr[%d] = %d \t\t at Address &ptr_Arr[%d]: %p\n",
            i, ptr_Arr[i], i, &ptr_Arr[i]);
    }

    printf("\n\n");
    for (int i = 0; i < intArrLength; i++)
    {
        printf("*(ptr_Arr + %d) = %d \t\t at Address (ptr_Arr + %d): %p\n",
            i, *(ptr_Arr + i), i, (ptr_Arr + i));
    }

    // Free the allocated memory
    if (ptr_Arr)
    {
        free(ptr_Arr);
        ptr_Arr = NULL;
        printf("\n\n");
        printf("Allocated memory is freed!\n\n");
    }

    return 0;
}
