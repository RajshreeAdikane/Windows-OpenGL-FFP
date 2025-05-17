#include <stdio.h>

int main(void)
{
	//code 
	unsigned int shree;
	unsigned int result;

	printf("\n\n");
	printf("Enter the value of shree = ");
	scanf("%u", &shree);

	printf("\n\n\n");
	result = ~shree;
	printf("Bitwise complement of shree is %d gives result %d\n\n", shree, result);
	return(0);

}