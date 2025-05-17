#include<stdio.h>

int main(void)
{
//if else ladder
	int num_RKA;

	printf("\n\n");

	printf("enter the number");
	scanf("%d", &num_RKA);

	if (num_RKA < 0)
	{
		printf("the number is NEGATIVE = %d", num_RKA);
	}
	else
	{
		if ((num_RKA > 1) && (num_RKA < 100))
		{
			printf("the number is between 0 to 100 = %d", num_RKA);
		}
		else
		{
			if ((num_RKA > 100) && (num_RKA < 200))
			{
				printf("the number is between 100 to 200 = %d", num_RKA);
			}
			else
			{
				if ((num_RKA > 200) && (num_RKA < 300))
				{
					printf("the number is between 200 to 300 = %d", num_RKA);
				}
				else
				{
					if ((num_RKA > 300) && (num_RKA < 400))
					{
						printf("the number is between 300 to 400 = %d", num_RKA);
					}
					else
					{
						if ((num_RKA > 400) && (num_RKA < 500))
						{
							printf("the number is between 400 to 500 = %d", num_RKA);
						}
						else
						{
							printf("number is greater than 500");
						}

					}
				}
			}
		}
	}


}