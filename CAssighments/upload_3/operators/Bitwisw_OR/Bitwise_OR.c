#include <stdio.h>

int main(void)
{
	//code 
	unsigned int or;
	unsigned int ga;
	unsigned int result;

	printf("\n\n");
	printf("Enter the value of or = ");
	scanf("%u", &or);

	printf("\n\n");
	printf("Enter the value of ga = ");
	scanf("%u", &ga);

	printf("\n\n\n");
	result = or | ga;
	printf("Bitwise OR operation of or = %d and ga = %d gives result = %d\n\n", or, ga, result);
	return(0);

}