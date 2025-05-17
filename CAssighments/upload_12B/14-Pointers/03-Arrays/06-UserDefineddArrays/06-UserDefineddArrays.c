#include <stdio.h>
#include <stdlib.h>

#define INT_SIZE sizeof(int)
#define FLOAT_SIZE sizeof(float)
#define CHAR_SIZE sizeof(char)
#define DOUBLE_SIZE sizeof(double)

int main(void)
{
    int* intArray;
    float* floatArray;
    char* charArray;
    double* doubleArray;

    int size, i;


    printf("Enter the size of the array: ");
    scanf("%d", &size);

    intArray = (int*)malloc(size * INT_SIZE);
    floatArray = (float*)malloc(size * FLOAT_SIZE);
    charArray = (char*)malloc(size * CHAR_SIZE);
    doubleArray = (double*)malloc(size * DOUBLE_SIZE);

    // Check if memory allocation was successful
    if (intArray == NULL || floatArray == NULL || charArray == NULL || doubleArray == NULL) {
        printf("Memory allocation failed!\n");
        // Free any already allocated memory before exiting
        if (intArray != NULL) free(intArray);
        if (floatArray != NULL) free(floatArray);
        if (charArray != NULL) free(charArray);
        if (doubleArray != NULL) free(doubleArray);
        return -1;
    }

    // Initialize the array elements with some values
    for (i = 0; i < size; i++) {
        intArray[i] = (i + 1) * 10;  // int: 10, 20, 30, ...
        floatArray[i] = (i + 1) * 1.5;  // float: 1.5, 3.0, 4.5, ...
        charArray[i] = 'A' + i;  // char: 'A', 'B', 'C', ...
        doubleArray[i] = (i + 1) * 2.5;  // double: 2.5, 5.0, 7.5, ...
    }

    // Print the array elements and their addresses
    printf("\nArray elements and their addresses:\n");

    printf("\nInteger Array:\n");
    for (i = 0; i < size; i++) {
        printf("intArray[%d] = %d \t Address = %p\n", i, intArray[i], &intArray[i]);
    }

    printf("\nFloat Array:\n");
    for (i = 0; i < size; i++) {
        printf("floatArray[%d] = %.2f \t Address = %p\n", i, floatArray[i], &floatArray[i]);
    }

    printf("\nChar Array:\n");
    for (i = 0; i < size; i++) {
        printf("charArray[%d] = %c \t Address = %p\n", i, charArray[i], &charArray[i]);
    }

    printf("\nDouble Array:\n");
    for (i = 0; i < size; i++) {
        printf("doubleArray[%d] = %.2f \t Address = %p\n", i, doubleArray[i], &doubleArray[i]);
    }

    if (intArray != NULL) {
        free(intArray);
        printf("\nMemory for intArray freed successfully.\n");
    }

    if (floatArray != NULL) {
        free(floatArray);
        printf("Memory for floatArray freed successfully.\n");
    }

    if (charArray != NULL) {
        free(charArray);
        printf("Memory for charArray freed successfully.\n");
    }

    if (doubleArray != NULL) {
        free(doubleArray);
        printf("Memory for doubleArray freed successfully.\n");
    }

    return 0;
}
