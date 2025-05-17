#include<stdio.h>

#define IS_PRIME 10

int main(void)
{
    int Array[IS_PRIME];

    printf("Enter %d numbers:\n", IS_PRIME);


    for (int i = 0; i < IS_PRIME; i++) {
        scanf("%d", &Array[i]);
    }

    printf("\nPrime numbers in the array are:\n");


    for (int i = 0; i < IS_PRIME; i++) {
        int num = Array[i];
        int is_prime = 1; 

        if (num <= 1) {
            is_prime = 0; 
        }

        for (int j = 2; j * j <= num; j++) {
            if (num % j == 0) {
                is_prime = 0; 
                break; 
            }
        }

        if (is_prime) {
            printf("%d ", num); 
        }
    }

    printf("\n");
    return 0;
}
