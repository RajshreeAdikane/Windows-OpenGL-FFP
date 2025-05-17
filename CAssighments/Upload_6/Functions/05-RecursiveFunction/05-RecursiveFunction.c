#include<stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	unsigned int A;
	void recursive(unsigned int);	

	printf("\n\n");
	printf("Enter Number:\n");
	scanf("%u", &A);
	printf("\n\n");
	printf("recursive function output is: \n\n");
	recursive(A);
	printf("\n\n");
	return 0;

}

void recursive(unsigned int A)
{
	printf("A = %d\n\n", A);
	if (A > 0)
		recursive(A - 1);

}