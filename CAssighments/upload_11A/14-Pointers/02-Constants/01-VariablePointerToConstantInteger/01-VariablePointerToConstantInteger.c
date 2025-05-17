#include<stdio.h>

int main(void)
{
	int num = 9;
	const int* ptr = NULL;

	ptr = &num;
	printf("\n\n");
	printf("value of num = %d\n", num);
	printf("value of ptr = %p\n", ptr);

	num++;
	printf("\n\n");
	printf("value of num++ =%d\n", num);

	ptr++;
	printf("\n\n");
	printf("ptr++ = %p\n", ptr);
	printf("value at this new ptr = %d\n", *ptr);

	return 0;
}