#include<stdio.h>

int main(void)
{
	int a;
	int* ptr = NULL;

	a = 9;
	ptr = &a;

	printf("a = %d\n", a);
	printf("&a = %p\n", &a);
	printf("*(&a) = %d\n", *(&a));
	printf("*ptr = %d\n", *ptr);
	printf("ptr = %p\n", ptr);

	printf("Answer of (ptr+10) = %p\n", (ptr + 10));
	printf("Answer of *(ptr+10) = %d\n", *(ptr + 10));
	printf("Answer of (*ptr+10) = %d\n", (*ptr + 10));
	++*ptr;
	printf("Answer of ++*ptr = %d\n", *ptr);
	ptr++;
	printf("Answer of *ptr++ = %p\n", ptr);
	ptr = &a;
	(*ptr)++;
	printf("Answer of (*ptr)++ = %d\n", *ptr);

	return 0;
}
