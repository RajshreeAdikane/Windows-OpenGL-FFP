#include <stdio.h>

int main(void)
{
    int a, b;
    int result;

    printf("\n\n");
    printf("Enter the first number (a):\n");
    scanf("%d", &a);

    printf("Enter the second number (b):\n");
    scanf("%d", &b);

    printf("\n\n");
    printf("If Answer is 0, it means 'FALSE'.\n");
    printf("If Answer is 1, it means 'TRUE'.\n\n");

    result = (a > 0) && (b > 0);
    printf("Logical AND (a > 0) && (b > 0): %d\n", result);

    result = (a > 0) || (b > 0);
    printf("Logical OR (a > 0) || (b > 0): %d\n", result);

    result = !(a > 0);
    printf("Logical NOT !(a > 0): %d\n", result);

    result = !(b > 0);
    printf("Logical NOT !(b > 0): %d\n", result);

    printf("\n");
    printf("Using logical operators with conditions:\n");
    result = (a > b) && (b > 0);
    printf("(a > b) && (b > 0): %d\n", result);

    result = (a < b) || (b < 0);
    printf("(a < b) || (b < 0): %d\n", result);

    return 0;
}
