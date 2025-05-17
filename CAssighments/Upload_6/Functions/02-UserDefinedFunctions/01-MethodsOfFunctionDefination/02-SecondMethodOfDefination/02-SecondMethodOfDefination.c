#include<stdio.h>


int main(int argc, char* argv[], char* envp[])
{
	int Addition(void);

	int result = Addition();
	printf("\n\n");

	printf("sum = %d \n\n",result);
	//Addition();
	return(0);
}

int Addition(void)
{
	int A1, B1, sum1;

	printf("\n\n");

	printf("Enter the number:\n");
	scanf("%d", &A1);

	printf("Enter the secon number:\n");
	scanf("%d", &B1);

	sum1 = A1 + B1;
	return(sum1);


}