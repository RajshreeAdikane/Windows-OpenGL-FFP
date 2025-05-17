#include<stdio.h>

int main(void)
{
	printf("\n\n");

	for (int i = 1; i <= 10; i++)
	{
		printf("i= %d\n", i);
		printf("----------\n\n");
		for (int j = 1; j <= 5; j++)
		{
			printf("\tj=%d\n", j);
			printf("\n");
		}
	}

	printf("\n\n");
	return(0);
}