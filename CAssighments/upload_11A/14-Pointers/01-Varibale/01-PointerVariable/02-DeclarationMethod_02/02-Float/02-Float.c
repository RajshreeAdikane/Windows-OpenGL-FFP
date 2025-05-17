#include<stdio.h>

int main(void)
{
	float Float_num;
	float* ptr = NULL;

	Float_num = 123.7f;
	printf("\n\n");
	printf("*****BEFORE ptr = &Float_num*****\n");

	printf("value of Float_num  = %f\n\n", Float_num);
	printf("Address of Float_num  = %p\n\n", &Float_num);
	printf("Value at adress of Float_num  = %f\n\n", *(&Float_num));

	//Assigh add or Float_num to ptr

	ptr = &Float_num;

	printf("*****AFTER ptr = &Float_num*****\n");
	printf("value of Float_num = %f\n\n", Float_num);
	printf("Address of Float_num = %p\n\n", ptr);
	printf("Value at adress of Float_num  = %f\n\n", *ptr);

	return 0;

}