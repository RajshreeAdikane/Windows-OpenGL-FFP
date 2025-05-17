#include<stdio.h>

int main(void)
{
	int a;
	int b;

	printf("\n\n");
	printf("Enter a Number:\n");
	scanf("%d", &a);

	printf("Enter a Number:\n");
	scanf("%d", &b);

	printf("A=%d\n", a);
	printf("A=%d\n", a++);
	printf("A=%d\n", a);
	printf("A=%d\n", ++a);

	printf("b=%d\n", b);
	printf("b=%d\n", b++);
	printf("b=%d\n", b);
	printf("b=%d\n", ++b);

	return 0;

}