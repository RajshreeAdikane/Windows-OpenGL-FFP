#include <stdio.h>

int main(void)
{
	//code 
	unsigned int a ;
	unsigned int bit;
	unsigned int result;

	printf("\n\n");
	printf("Enter the value of a = ");
	scanf("%u", &a );

	printf("\n\n");
	printf("Enter the value of bits in which ho many bits you want to shift = ");
	scanf("%u", &bit);

	printf("\n\n\n");
	result =a >> bit;
	printf("bitwise right shift of a is %d by right shift of %d the result is %d", a, bit, result);
	return(0);

}