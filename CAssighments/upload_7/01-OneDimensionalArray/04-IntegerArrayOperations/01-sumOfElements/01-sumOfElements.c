#include<stdio.h>

#define ARRAY_NUM_ELE 5

int main(void)
{
    int Array[ARRAY_NUM_ELE];
    int sum = 0;

    printf("\n\n");
    printf("Enter the elements 5:\n");

    for (int i = 0; i < ARRAY_NUM_ELE; i++) {
        scanf("%d", &Array[i]);
    }

    printf("\nElements entered by you:\n\n");
    for (int i = 0; i < ARRAY_NUM_ELE; i++) {
        printf("%d ", Array[i]);
        sum = sum + Array[i];
    }
    printf("the addition of an array elements are: %d", sum);

    printf("\n");
    return 0;
}
