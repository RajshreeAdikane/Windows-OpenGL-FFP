#include<stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	char Array[MAX_STRING_LENGTH];

	printf("\n\n");
	printf("Enter a string: \n\n");
	gets_s(Array, MAX_STRING_LENGTH);

	printf("\n\n");
	printf("Original string entered by you is: %s\n\n", Array);

	strrev(Array);
	printf("Reverse string is: %s\n\n", Array);

	return 0;
}
