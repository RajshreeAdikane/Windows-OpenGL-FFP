#include<stdio.h>

#define ARRAY_NUM_ELE 10

int main(void)
{
    int Array[ARRAY_NUM_ELE];
    int sum = 0;

    printf("\n\n");
    printf("Enter %d elements:\n", ARRAY_NUM_ELE);

    // Input Array Elements
    for (int i = 0; i < ARRAY_NUM_ELE; i++) {
        scanf("%d", &Array[i]);
    }

    printf("\nEven numbers are:\n");
    for (int i = 0; i < ARRAY_NUM_ELE; i++) {
        if (Array[i] % 2 == 0) {
            printf("%d ", Array[i]);
        }
    }

    printf("\n\nOdd numbers are:\n");
    for (int i = 0; i < ARRAY_NUM_ELE; i++) {
        if (Array[i] % 2 != 0) {
            printf("%d ", Array[i]);
        }
    }

    printf("\n");
    return 0;
}
