#include<stdio.h>


int main(int argc, char *argv[], char *envp[])
{
	void Addition(void);

	Addition();
	return(0);
}

void Addition(void)
{
	int a, b, sum;

	printf("\n\n");

	printf("Enter the number:\n");
	scanf("%d", &a);

	printf("Enter the secon number:\n");
	scanf("%d", &b);

	sum = a + b;

	printf("the sum of the numbers %d and %d is: %d \n\n", a, b, sum);


}