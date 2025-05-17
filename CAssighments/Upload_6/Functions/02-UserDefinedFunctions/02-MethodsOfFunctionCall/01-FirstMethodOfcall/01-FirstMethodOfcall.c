#include <stdio.h>

// Function Prototypes
void Addition(void);
int Subtraction(void);
void Multiplication(int, int);
int Division(int, int);

int main(int argc, char* argv[], char* envp[]) {
    int a, b;
    int a_mul, b_mul;
    int a_div, b_div;
    int result;

    // Addition
    Addition();

    // Subtraction
    printf("\n\n");
    result = Subtraction(); 
    printf("Subtraction result: %d\n\n", result);

    // Multiplication
    printf("\n\n");
    printf("Enter the first number for multiplication:\n");
    scanf("%d", &a_mul);

    printf("Enter the second number for multiplication:\n");
    scanf("%d", &b_mul);

    Multiplication(a_mul, b_mul);

    // Division
    printf("\n\n");
    printf("Enter the first number for division:\n");
    scanf("%d", &a_div);

    printf("Enter the second number for division:\n");
    scanf("%d", &b_div);

    result = Division(a_div, b_div);
    printf("Division result of %d and %d is: %d\n\n", a_div, b_div, result);

    return 0;
}

// Addition Function
void Addition(void) {
    int a, b, sum;

    printf("\n\n");
    printf("Enter the first number:\n");
    scanf("%d", &a);

    printf("Enter the second number:\n");
    scanf("%d", &b);

    sum = a + b;
    printf("The sum of %d and %d is: %d\n\n", a, b, sum);
}

// Subtraction Function
int Subtraction(void) {
    int a, b, subtraction;

    printf("\n\n");
    printf("Enter the first number:\n");
    scanf("%d", &a);

    printf("Enter the second number:\n");
    scanf("%d", &b);

    subtraction = a - b;
    return subtraction;
}

// Multiplication Function
void Multiplication(int a_mul, int b_mul) {
    int mul;

    mul = a_mul * b_mul;
    printf("Multiplication of %d and %d is: %d\n\n", a_mul, b_mul, mul);
}

// Division Function
int Division(int a_div, int b_div) {
    int div_quo;

    if (b_div == 0) {
        printf("Error: Division by zero is not allowed.\n");
        exit(1); 
    }

    div_quo = a_div / b_div; 
    return div_quo;
}
