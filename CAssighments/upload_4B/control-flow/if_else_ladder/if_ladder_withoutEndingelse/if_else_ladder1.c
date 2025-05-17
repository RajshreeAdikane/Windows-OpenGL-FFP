#include<stdio.h>

int main(void)
{
	//if else ladder
	int num;
	printf("\n\n");

	printf("Enter the number");
	scanf("%d", &num);

	if (num < 0) {
		printf("the number is negative = %d", num);
	}
	else if ((num > 1) && (num < 100))
	{
		printf("the number is between 1 to  100 = %d", num);
	}
	else if ((num > 100) && (num < 200))
	{
		printf("the number is between 100 to  200 = %d", num);
	}
	else if ((num > 200) && (num < 300))
	{
		printf("the number is between 200 to  300 = %d", num);
	}
	else if ((num > 300) && (num < 400))
	{
		printf("the number is between 300 to  400 = %d", num);
	}
	else if ((num > 400) && (num < 500))
	{
		printf("the number is between 400 to  500 = %d", num);
	}
	else if (num>500)
	{
		printf("the number is greater than 500 = %d", num);
	}

	return(0);

}