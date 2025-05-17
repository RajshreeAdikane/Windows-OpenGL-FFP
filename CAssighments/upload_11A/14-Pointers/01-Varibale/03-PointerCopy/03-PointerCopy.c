#include<stdio.h>

int main(void)
{
	int a;
	int* ptr = NULL;
	int* copy_ptr = NULL;

	a = 9;
	ptr = &a;

	printf("\n\n");
	printf("***** BEFORE copy_ptr = ptr *****\n");
	printf("a = %d\n", a);
	printf("&a = %p\n", &a);
	printf("*(&a) = %d\n", *(&a));
	printf("*ptr = %d\n", *ptr);
	printf("ptr = %p\n", ptr);

	copy_ptr = ptr;

	printf("\n***** AFTER copy_ptr = ptr *****\n");
	printf("a = %d\n", a);
	printf("&a = %p\n", &a);
	printf("*(&a) = %d\n", *(&a));
	printf("*ptr = %d\n", *ptr);
	printf("ptr = %p\n", ptr);

	return 0;
}
