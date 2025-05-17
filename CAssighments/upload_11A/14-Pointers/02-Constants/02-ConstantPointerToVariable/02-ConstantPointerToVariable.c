#include<stdio.h>

int main(void)
{
	int num = 9;
	int* const ptr = &num;

	//ptr = &num;
	printf("\n\n");
	printf("value of num = %d\n", num);
	printf("value of ptr address= %p\n", ptr);

	num++;
	printf("\n\n");
	printf("value of num++ =%d\n", num);

	(*ptr)++;
	printf("\n\n");
	printf("ptr++ value = %p\n", ptr); //The address stored in ptr remains unchanged because ptr is a constant pointer.
	printf("value at this new ptr = %d\n", *ptr);
		
	return 0;
}