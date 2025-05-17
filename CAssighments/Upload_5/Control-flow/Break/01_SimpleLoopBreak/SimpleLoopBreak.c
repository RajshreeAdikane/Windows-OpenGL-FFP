#include<stdio.h>
#include<conio.h>

int main(void)
{
	int i;
	char ch;
	printf("\n\n");
	printf("printing Even numbers every user input\n\n");
	printf("Enter 'Q' or 'q' to exiting the loop\n\n");

	for (i = 1; i <= 100; i++)
	{
		printf("\t%d\n", i);
		ch = getch();
			if (ch == 'Q' || ch == 'q')
			{
				break;
			}
	}
	printf("\n\n");
	printf("exititing Loop");
	return(0);

}