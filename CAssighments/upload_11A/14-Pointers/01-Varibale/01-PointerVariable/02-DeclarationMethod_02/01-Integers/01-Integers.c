#include<stdio.h>

int main(void)
{
	int num;
	int* ptr = NULL;

	num = 3;
	printf("\n\n");
	printf("**********BEFORE ptr = &num*****\n");

	printf("value of num  = %d\n\n", num);
	printf("Address of num  = %p\n\n", &num);
	printf("Value at adress of num  = %d\n\n", *(&num));

	//Assigh add or num to ptr

	ptr = &num;

	printf("**********AFTER ptr = &num*****\n");
	printf("value of num = %d\n\n", num);
	printf("Address of num = %p\n\n", ptr);
	printf("Value at adress of num  = %d\n\n", *ptr);

	return 0;

}