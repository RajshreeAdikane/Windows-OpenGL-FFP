#include <stdio.h>

int main(void)
{
	//code 


	unsigned int a;
	unsigned int b;
	unsigned int c;

	printf("\n\n");
	printf("Enter the value of a = ");
	scanf("%u", &a);

	printf("\n\n");
	printf("Enter the value of b = ");
	scanf("%u", &b);

	printf("\n\n\n");
	c = a & b;
	printf("Bitwise AND operation of a = %d and b = %d gives c = %d\n\n", a, b, c);


	return(0);

}