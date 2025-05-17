#include<stdio.h>

int main(void)
{
	void SwapNumbers(int, int);

	int a, b;
	printf("\n\n");
	printf("Enter the value of A:\n");
	scanf("%d", &a);

	printf("Enter the value of B:\n");
	scanf("%d", &b);

	printf("********BEFORE SWAPING***********\n\n");
	printf("Value of A is:%d\n", a);
	printf("Value of B is:%d\n", b);

	SwapNumbers(a, b);

	printf("\n\n");
	printf("********AFTER SWAPING***********\n\n");
	printf("Value of A is:%d\n", a);
	printf("Value of B is:%d\n", b);

	printf("\n\n");

	return 0;

}

void SwapNumbers(int x, int y)
{
	int temp;

	printf("********BEFORE SWAPING***********\n\n");
	printf("Value of x is:%d\n", x);
	printf("Value of y is:%d\n", y);

	temp = x;
	x = y;
	y = temp;

	printf("********AFTER SWAPING***********\n\n");
	printf("Value of x is:%d\n", x);
	printf("Value of y is:%d\n", y);

}