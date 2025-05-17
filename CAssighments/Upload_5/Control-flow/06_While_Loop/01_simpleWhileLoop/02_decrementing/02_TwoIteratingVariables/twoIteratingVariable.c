#include<stdio.h>

int main(void)
{
	printf("\n\n");

	printf("Printing 10 to 1 and 100 to 10: \n\n");

	int i = 10, j = 100;
	while (i >= 1 && j >= 10)
	{
		printf("\t%d \t%d\n", i, j);
		i--;
		j = j - 10;
	}
	printf("\n\n");

	return(0);
}