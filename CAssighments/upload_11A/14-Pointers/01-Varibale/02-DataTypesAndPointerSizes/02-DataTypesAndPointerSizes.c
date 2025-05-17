#include<stdio.h>

struct Employee
{
	char name[200];
	int age;
	float salary;
	char sex;
	char marital_status;
};

int main(void)
{
	printf("\n\n");
	printf("sizes of data types and pointers:\n\n");
	printf("size of int : %d \t \t \t size of pointer to int* :%d\n\n ", sizeof(int), sizeof(int*));
	printf("size of float : %d \t \t \t size of pointer to float* :%d\n\n ", sizeof(float), sizeof(float*));
	printf("size of double : %d \t \t \t size of pointer to double* :%d\n\n ", sizeof(double), sizeof(double*));
	printf("size of char : %d \t \t \t size of pointer to char* :%d\n\n ", sizeof(char), sizeof(char*));
	printf("size of struct Employee : %d \t \t \t size of pointer to struct Employee* :%d\n\n ", sizeof(struct Employee), sizeof(struct Employee*));

	return 0;
}