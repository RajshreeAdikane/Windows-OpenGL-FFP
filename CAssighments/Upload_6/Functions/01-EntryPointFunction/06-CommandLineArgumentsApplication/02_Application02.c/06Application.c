#include<stdio.h>
#include<conio.h>


int main(int argc, char* argv[], char* evp[])
{
	if (argc != 4) //program name +first name +middle name +surname =4 command line arguments required
	{
		printf("\n\n");
		printf("Invalid usage!!! exiting now...\n\n");
		printf("Usage: CommandLineArguments <first name> <middle name> <surname>\n\n");
		exit(0);
	}
	// this program prints your full name as entres in commnd line arg
	//argv[0] = prog name itself

	printf("\n\n");
	printf("Your full name is: \n");
	for (int i = 1; i < argc; i++)// loop start at 1 
	{
		printf("%s", argv[i]);

	}
	return(0);


}