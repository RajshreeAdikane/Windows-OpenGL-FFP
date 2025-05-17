#include<stdio.h>


int main(void)
{
    void MathOperations(int, int, int*, int*, int*, int*, int*);
    int a, b;
    int ans_sum;
    int ans_diff;
    int ans_mul;
    int ans_remainder;
    int ans_quotient;

    printf("\n\n");
    printf("Enter the value of A: \n");
    scanf("%d", &a);
    printf("Enter the value of B: \n");
    scanf("%d", &b);

    MathOperations(a, b, &ans_sum, &ans_diff, &ans_mul, &ans_remainder, &ans_quotient);

    printf("\n\n");
    printf("Sum: %d\n", ans_sum);
    printf("Difference: %d\n", ans_diff);
    printf("Multiplication: %d\n", ans_mul);
    printf("Remainder: %d\n", ans_remainder);
    printf("Quotient: %d\n", ans_quotient);
    printf("\n\n");

    return 0;
}

void MathOperations(int x, int y, int* sum, int* diff, int* mul, int* remainder, int* quotient)
{
    *sum = x + y;
    *diff = x - y;
    *mul = x * y;
    *remainder = x % y;
    *quotient = x / y;
}
