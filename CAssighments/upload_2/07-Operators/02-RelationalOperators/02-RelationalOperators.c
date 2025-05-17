#include<stdio.h>

int main(void)
{
    int a;
    int b;
    int result;

    printf("\n\n");
    printf("Enter a Number:\n");
    scanf("%d", &a);

    printf("Enter another Number:\n");
    scanf("%d", &b);

    printf("\n\n");
    printf("If Answer is 0, it means 'FALSE'.\n");
    printf("If Answer is 1, it means 'TRUE'.\n\n");

    result = (a > b);
    printf("A (%d) is greater than B (%d): a > b = %d\n", a, b, result);

    result = (a < b);
    printf("A (%d) is less than B (%d): a < b = %d\n", a, b, result);

    result = (a >= b);
    printf("A (%d) is greater than or equal to B (%d): a >= b = %d\n", a, b, result);

    result = (a <= b);
    printf("A (%d) is less than or equal to B (%d): a <= b = %d\n", a, b, result);

    result = (a == b);
    printf("A (%d) is equal to B (%d): a == b = %d\n", a, b, result);

    result = (a != b);
    printf("A (%d) is not equal to B (%d): a != b = %d\n", a, b, result);

    return 0;
}
