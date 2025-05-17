#include <stdio.h>
#include <conio.h>

int main(void)
{
	int RKA_option, ch = '\0';

	//code

	printf("\n\n");
	printf("When the Infinit loop begines enter the 'R' or 'r' to quit the loop\n");
	printf("enter the 'A' or 'a' to start user controlled infinite loop\n");

	RKA_option = getch();
	if (RKA_option == 'A' || RKA_option == 'a')
	{
		for (;;)
		{
			printf("You have entered in a infinte loop......\n");
			ch = getch();
			if (ch == 'R' || ch == 'r')
			{
				break;
			}
		}
		printf("\n\n");
		printf("You have controlled the infinite loop\n");
		return(0);
	}
}