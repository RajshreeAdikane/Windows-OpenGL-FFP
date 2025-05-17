#include<stdio.h>


int main(int argc, char *argv[])
{
	//Entry-point function is main() valid return() type (int) and 2 (int argc, char *argv[])
	printf("Hello World Rajashree Adikane return type \n\n");
	printf("Number of command line arguements = %d\n\n", argc);
	printf("command line arguments passed in this program are :\n\n");

	for (int i = 0; i < argc; i++)
	{
		printf("command line argument number %d = %s\n ", (i + 1), argv[i]);

	}
	printf("\n\n");
	return(0);
}