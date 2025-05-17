#include<stdio.h>

int main(void)
{
	int iArray[10];

	for (int i = 0; i < 10; i++)
	{
		iArray[i] = (i + 1) * 3;
	}
	printf("\n\n");
	printf("Elements of the Integer array and Addresses: \n\n");
	for (int i = 0; i < 10; i++)
	{
		printf("iArray[%d]=%d \t Address =%p\n", i, iArray[i],&iArray[i]);
	}
	printf("\n\n");

	return 0;
}