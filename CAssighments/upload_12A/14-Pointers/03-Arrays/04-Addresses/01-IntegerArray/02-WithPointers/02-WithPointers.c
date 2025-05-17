#include<stdio.h>

int main(void)
{
	int iArray[10];
	int* ptr_Array = NULL;

	for (int i = 0; i < 10; i++)
	{
		iArray[i] = (i + 1) * 3;
	}
	ptr_Array = iArray;
	printf("\n\n");
	printf("Elements of the Integer array and Addresses: \n\n");
	for (int i = 0; i < 10; i++)
	{
		printf("iArray[%d]=%d \t Address =%p\n", i, *(ptr_Array +i), (ptr_Array+i));
	}
	printf("\n\n");

	return 0;
}