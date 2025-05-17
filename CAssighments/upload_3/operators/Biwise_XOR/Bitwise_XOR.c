#include <stdio.h>

int main(void)
{
	//code 
	unsigned int r;
	unsigned int g;
	unsigned int result;

	printf("\n\n");
	printf("Enter the value of r = ");
	scanf("%u", &r);

	printf("\n\n");
	printf("Enter the value of g = ");
	scanf("%u", &g);

	printf("\n\n\n");
	result = r^g;
	printf("Bitwise XOR operation of r = %d and g = %d gives result = %d\n\n", r, g, result);
	return(0);

}