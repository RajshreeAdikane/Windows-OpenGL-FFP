#include <stdio.h>

int main(void)
//code

{
	printf("\n\n");
	printf("size of 'int' =%Id bytes \n", sizeof(int));
	printf("size of 'unsigned int' =%Id bytes \n", sizeof(unsigned int));
	printf("size of 'long' =%Id bytes \n", sizeof(long));
	printf("size of 'long long' =%Id bytes \n", sizeof(long long));
	printf("size of 'float' =%Id bytes \n", sizeof(float));
	printf("size of 'double' =%Id bytes \n", sizeof(double));
	printf("size of 'long double = %Id bytes \n", sizeof(long double));
	printf("\n\n");
	return(0);
}