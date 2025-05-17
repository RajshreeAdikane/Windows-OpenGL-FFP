#include<stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	char Array[MAX_STRING_LENGTH];
	char Array_copy[MAX_STRING_LENGTH];
	int isStringlength = 0;

	printf("\n\n");
	printf("Enter a string: \n\n");
	gets_s(Array, MAX_STRING_LENGTH);
	strcpy(Array_copy, Array);

	printf("\n\n");
	printf("Orinal string entered by you is: %s\n\n", Array);

	isStringlength = strlen(Array);
	printf("Copy string is: %s\n\n", Array_copy);

	return 0;


}