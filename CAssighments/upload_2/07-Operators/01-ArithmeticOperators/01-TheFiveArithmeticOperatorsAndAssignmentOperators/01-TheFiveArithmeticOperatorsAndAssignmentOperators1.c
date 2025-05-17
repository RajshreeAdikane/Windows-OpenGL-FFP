#include<stdio.h>

int main(void)
{
	int a, b;
	int result;

	printf("\n\n");
	printf("Enter A number:\n");
	scanf("%d", &a);

	printf("Enter A number:\n");
	scanf("%d", &b);

	result = a + b;
	printf("Addition of two numbers %d and %d is: %d \n",a,b, result);

	result = a - b;
	printf("Substraction of two numbers %d and %d is: %d \n",a,b, result);

	result = a * b;
	printf("Multiplication of two numbers %d and %d is: %d \n", a, b, result);

	result = a / b;
	printf("Division of two numbers %d and %d gives Quotient is: %d \n",a,b, result);

	result = a % b;
	printf("Division of two numbers %d and %d gives Remainder is: %d \n",a,b, result);

	printf("\n\n");


}