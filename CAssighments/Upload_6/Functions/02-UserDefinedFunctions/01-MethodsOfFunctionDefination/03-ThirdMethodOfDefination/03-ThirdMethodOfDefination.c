#include<stdio.h>


int main(int argc, char* argv[], char* envp[])
{
	void Addition(int , int);
	int a, b;
	printf("Enter the number:\n");
	scanf("%d", &a);

	printf("Enter the secon number:\n");
	scanf("%d", &b);

	Addition(a,b);
	return(0);
}

void Addition(int a, int b)
{
	int sum;
	printf("\n\n");
	sum = a + b;
	printf("the sum of the numbers %d and %d is: %d \n\n", a, b, sum);

}