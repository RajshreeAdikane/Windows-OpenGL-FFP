#include <stdio.h>
#include <stdlib.h>

void MyAlloc(int** ptr, unsigned int numberOfElements);

int main(void) {
    int* Array = NULL;
    unsigned int num_elements;

    printf("\nEnter the number of elements in the int array:\n");
    scanf("%u", &num_elements);

    printf("\n");
    MyAlloc(&Array, num_elements);

    printf("Enter elements to fill up your int array:\n");
    for (int i = 0; i < num_elements; i++) {
        scanf("%d", &Array[i]);
    }

    printf("\nThe elements in your int array are:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%d ", Array[i]);
    }

    printf("\n");

    if (Array) {
        free(Array);
        Array = NULL;
        printf("\nMemory allocated successfully freed.\n");
    }

    return 0;
}

void MyAlloc(int** ptr, unsigned int numberOfElements) {
    *ptr = (int*)malloc(numberOfElements * sizeof(int));

    if (*ptr == NULL) {
        printf("Could not allocate memory.\n");
        exit(0);
    }

    printf("MyAlloc() has successfully allocated %lu bytes for the int array.\n",
        (unsigned long)(numberOfElements * sizeof(int)));
}
