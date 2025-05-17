#include<stdio.h>

int main(void)
{
	//months using if else ladder

	int Month_RKA;

	printf("\n\n");

	printf("Enter the Number of Month_RKA\n\n");
	scanf("%d", &Month_RKA);

	if (Month_RKA == 1)
		printf("the Month_RKA number is %d JANUARY \n", Month_RKA);
	else if (Month_RKA == 2)
		printf("the Month_RKA number is %d FEBRUARY \n", Month_RKA);
	else if (Month_RKA == 3)
		printf("the Month_RKA number is %d MARCH \n", Month_RKA);
	else if (Month_RKA == 4)
		printf("the Month_RKA number is %d APRIL \n", Month_RKA);
	else if (Month_RKA == 5)
		printf("the Month_RKA number is %d MAY \n", Month_RKA);
	else if (Month_RKA == 6)
		printf("the Month_RKA number is %d JUNE \n", Month_RKA);
	else if (Month_RKA == 7)
		printf("the Month_RKA number is %d JULY \n", Month_RKA);
	else if (Month_RKA == 8)
		printf("the Month_RKA number is %d AUGUST \n", Month_RKA);
	else if (Month_RKA == 9)
		printf("the Month_RKA number is %d SEPTEMBER \n", Month_RKA);
	else if (Month_RKA == 10)
		printf("the Month_RKA number is %d OCTOBER \n", Month_RKA);
	else if (Month_RKA == 11)
		printf("the Month_RKA number is %d NOVEMBER \n", Month_RKA);
	else if (Month_RKA == 12)
		printf("the Month_RKA number is %d DECEMBER \n", Month_RKA);
	else
		printf("INVALID Month_RKA ENTERED = %d \n", Month_RKA);

	return(0);


}