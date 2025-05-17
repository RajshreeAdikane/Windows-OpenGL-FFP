#include<stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	int My_strlen(char[]);
	char Array[MAX_STRING_LENGTH];
	int isStringlength = 0;

	printf("\n\n");
	printf("Enter a string: \n\n");
	gets_s(Array, MAX_STRING_LENGTH);

	printf("\n\n");
	printf("string entered by you is: %s\n\n", Array);

	isStringlength = My_strlen(Array);
	printf("string length is: %d\n\n", isStringlength);

	return 0;


}

int My_strlen(char str[])
{
	int str_length = 0;
	for (int i = 0; i < MAX_STRING_LENGTH; i++)
	{
		if (str[i] == '\0')
			break;
		else
			str_length++;

	}
	return (str_length);
}
