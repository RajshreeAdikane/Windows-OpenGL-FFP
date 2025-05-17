#include<stdio.h>


int main(int argc, char* argv[], char* envp[])
{
	int Addition(int, int);
	int a, b;
	printf("Enter the number:\n");
	scanf("%d", &a);

	printf("Enter the secon number:\n");
	scanf("%d", &b);

	int result = Addition(a, b);
	printf("\n\n");
	printf("sum = %d \n\n", result);
	return(0);
}

int Addition(int a, int b)
{
	int sum;
	sum = a + b;
	
	return(sum);

}