#include <stdio.h>

int main(void)
{
	//code 
	unsigned int num;
	unsigned int left_bit;
	unsigned int result;

	printf("\n\n");
	printf("Enter the value of a = ");
	scanf("%u", &num);

	printf("\n\n");
	printf("Enter the value of bits in which ho many bits you want to shift = ");
	scanf("%u", &left_bit);

	printf("\n\n\n");
	result = num << left_bit;
	printf("bitwise left shift of num is %d by left shift of %d the result is %d", num, left_bit, result);
	return(0);

}