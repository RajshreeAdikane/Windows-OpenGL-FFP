#include <stdio.h>
#include <stdlib.h>
 

struct MyData
{
	int i;
	float f;
	double d;
};

int main(void)
{
	void ChangeValues(struct MyData*);
	struct MyData* data = NULL;

	printf("\n\n");

	data = (struct MyData*)malloc(sizeof(struct MyData));
	if (data == NULL)
	{
		printf("Failed to allocate memory\n\n");
		exit(0);
	}
	else
		printf("Successfully memory allocated\n\n");


	data->i = 45;

	data->f = 12.12;

	data->d = 12.234566;

	printf("\n\n");
	printf("Data members of struct data");
	printf("int = %d\n", data->i);

	printf("float = %f\n", data->f);

	printf("double = %lf\n", data->d);

	ChangeValues(data);

	printf("Data members of struct data");
	printf("int = %d\n", data->i);

	printf("float = %f\n", data->f);

	printf("double = %lf\n", data->d);


	if (data)
	{
		free(data);
		data = NULL;
		printf("Memory alloccated to struct MyData\n\n");
	}

	return 0;
	
}

void ChangeValues(struct MyData* pParam_Data)
{
	pParam_Data->i = 9;
	pParam_Data->f = 7.5f;
	pParam_Data->d = 6.9898;

}