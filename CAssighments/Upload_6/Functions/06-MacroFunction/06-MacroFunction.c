#include <stdio.h>

#define MAX_NUMBER(a, b) ((a > b) ? a : b)

int main(int argc, char* argv[], char* envp[])
{
    int num1, num2;
    int result;

    printf("\n\n");
    printf("Enter the value of number one:\n");
    scanf("%d", &num1);

    printf("Enter the value of number two:\n");
    scanf("%d", &num2);

    result = MAX_NUMBER(num1, num2);
    printf("The result of the macro function is: %d\n", result);

    return 0;
}
