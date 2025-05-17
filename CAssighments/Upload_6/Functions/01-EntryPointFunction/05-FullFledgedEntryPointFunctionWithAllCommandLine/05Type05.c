#include<stdio.h>


int main(int argc, char* argv[], char *evp[])
{
	//Entry-point function is main() valid return() type (int) and 3 (int argc, char *argv[], char *envp[])
	printf("Hello World Rajashree Adikane return type \n\n");
	printf("Number of command line arguements = %d\n\n", argc);
	printf("command line arguments passed in this program are :\n\n");

	for (int i = 0; i < argc; i++)
	{
		printf("command line argument number %d = %s\n ", (i + 1), argv[i]);

	}
	printf("\n\n");
	printf("first 20 environental variables passd to this program are: \n\n");
	for(int i=0; i<20; i++)
	{
		printf("Environmrntal varibale Number %d =%s\n", (i + 1), evp[i]);
	}
	printf("\n\n");
	return(0);
}