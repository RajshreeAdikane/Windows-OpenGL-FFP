#include<stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{

	char Array_str[10][15] = { "Hello!","Welcome","To", "AMC", "Rajashree", "Kashinath", "Adikane", "2024","Roll no", "020"};

	int char_Size;
	int Array_str_size;
	int Array_str_num_ele, Array_str_num_rows, Array_str_num_col;
	int num_chars = 0;

	printf("\n\n");

	char_Size = sizeof(char);
	Array_str_size = sizeof(Array_str);

	printf("The size of an 2D Array is %d\n\n", Array_str_size);

	Array_str_num_rows = Array_str_size / sizeof(Array_str[0]);

	Array_str_num_col = sizeof(Array_str[0]) / sizeof(Array_str[0][0]);

	Array_str_num_ele = Array_str_num_rows * Array_str_num_col;

	for (int i = 0; i < Array_str_num_rows; i++)
	{
		num_chars = num_chars + Mystrlen(Array_str[i]);
	}
	printf("NUmbers of char present in 2D array=%d\n\n", num_chars);

	printf("strings in the array:\n\n");

	printf("%s", Array_str[0]);
	printf("%s", Array_str[1]);
	printf("%s", Array_str[2]);
	printf("%s", Array_str[3]);
	printf("%s", Array_str[4]);
	printf("%s", Array_str[5]);
	printf("%s", Array_str[6]);
	printf("%s", Array_str[7]);
	printf("%s", Array_str[8]);
	printf("%s\n\n", Array_str[9]);
	


	return 0;



}

int Mystrlen(char str[])
{
	int str_length = 0;
	for (int i = 0; i < MAX_STRING_LENGTH; i++)
	{
		if(str[i] == '/0')
			break;
		else
			str_length++;

	}
	return(str_length);
}