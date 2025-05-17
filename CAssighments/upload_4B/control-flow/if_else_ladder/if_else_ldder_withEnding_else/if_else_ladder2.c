#include<stdio.h>

int main(void)
{
	//if else ladder with else statement
	int num_RKA1;
	printf("\n\n");

	printf("Enter the number");
	scanf("%d", &num_RKA1);

	if (num_RKA1 < 0) {
		printf("the number is negative = %d", num_RKA1);
	}
	else if ((num_RKA1 > 1) && (num_RKA1 < 100))
	{
		printf("the number is between 1 to  100 = %d", num_RKA1);
	}
	else if ((num_RKA1 > 100) && (num_RKA1 < 200))
	{
		printf("the number is between 100 to  200 = %d", num_RKA1);
	}
	else if ((num_RKA1 > 200) && (num_RKA1 < 300))
	{
		printf("the number is between 200 to  300 = %d", num_RKA1);
	}
	else if ((num_RKA1 > 300) && (num_RKA1 < 400))
	{
		printf("the number is between 300 to  400 = %d", num_RKA1);
	}
	else if ((num_RKA1 > 400) && (num_RKA1 < 500))
	{
		printf("the number is between 400 to  500 = %d", num_RKA1);
	}
	else if (num_RKA1 > 500)
	{
		printf("the number is greater than 500 = %d", num_RKA1);
	}
	else
	{
		printf("Invalid Number");
}

	return(0);

}