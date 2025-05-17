#include<stdio.h>

#define INT_ARRAY_SIZE 5
#define FLOAT_ARRAY_SIZE 5 

struct MyData
{
	int Array_int[INT_ARRAY_SIZE];
	float Array_float[FLOAT_ARRAY_SIZE];
};

int main(void)
{
	struct MyData data_one;

	//piece-meal 
	data_one.Array_float[0] = 1.2f;
	data_one.Array_float[1] = 2.2f;
	data_one.Array_float[2] = 3.2f;
	data_one.Array_float[3] = 4.2f;
	data_one.Array_float[4] = 5.2f;

	//user input
	printf("\n\n");
	printf("enter the Integer values: \n\n");
	for (int i = 0; i < INT_ARRAY_SIZE; i++)
	{
		scanf("%d", &data_one.Array_int[i]);
	}
	
	//Displaying dataone and their values
	printf("\n\n");
	printf("The data memebers and their values are: \n\n");
	printf("Integer Array :\n");
	for (int i = 0; i < INT_ARRAY_SIZE; i++)
	{
		printf("integer array one[%d] = %d\n\n", i, data_one.Array_int[i]);
	}
	printf("Float Array :\n");
	for (int i = 0; i < FLOAT_ARRAY_SIZE; i++)
	{
		printf("Float array one[%d] = %f\n\n", i, data_one.Array_float[i]);
	}

	printf("\n\n");

	return 0;
}