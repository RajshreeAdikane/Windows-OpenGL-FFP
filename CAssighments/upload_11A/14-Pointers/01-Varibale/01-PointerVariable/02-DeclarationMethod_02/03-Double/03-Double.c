#include<stdio.h>

int main(void)
{
	double double_num;
	double* ptr = NULL;

	double_num = 4.56378879f;
	printf("\n\n");
	printf("*****BEFORE ptr = &double_num*****\n");

	printf("value of double_num  = %lf\n\n", double_num);
	printf("Address of double_num  = %p\n\n", &double_num);
	printf("Value at adress of double_num  = %lf\n\n", *(&double_num));

	//Assigh add or double_num to ptr

	ptr = &double_num;

	printf("*****AFTER ptr = &double_num*****\n");
	printf("value of double_num = %lf\n\n", double_num);
	printf("Address of double_num = %p\n\n", ptr);
	printf("Value at adress of double_num  = %lf\n\n", *ptr);

	return 0;

}