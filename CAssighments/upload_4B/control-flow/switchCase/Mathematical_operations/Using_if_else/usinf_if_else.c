#include<stdio.h>
#include<conio.h>

int main(void)
{
	//using if else ladder for mathatical oprations
	int a, b;
	int result;

	char option, option_division;

	printf("\n\n");
	printf("Enter the a:\n");
	scanf("%d", &a);

	printf("Enter the b:\n");
	scanf("%d", &b);

	printf("Enter the option for a operation:\n\n");
	printf("'A' or 'a' for ADD\n");
	printf("'S' or 's' for SUBS\n");
	printf("'M' or 'm' for MUL\n");
	printf("'D' or 'd' for DIV\n");
	
	printf("Enter the option");
	option = getch();

	printf("\n\n");

	if (option == 'A' || option == 'a')
	{
		result = a + b;
		printf("Addion of a = %d and b= %d\n gives result =%d \n", a,b,result);
	}
	else if (option == 'S' || option == 's')
	{
		if (a > b) 
		{
			result = a - b;
			printf("Substraction a = %d and b= %d gives result = %d\n", a, b, result);
			}
		else
		{
			result = b - a;
			printf("Substraction a = %d and b= %d gives result = %d\n", a, b, result);
		}
	}
	else if (option == 'M' || option == 'm')
	{
		result = a* b;

		printf("multimplication of a = %d and b = %d gives result = %d\n", a, b, result);
	}
	else if (option == 'D' || option == 'd')
	{
		printf("Enter the option in character:\n");
		printf("'Q' or 'q' or '/' for Quotient upon Divivon\n");
		printf("'R' or 'r' or '%' for Remainder upon Divivon\n");

		printf("Enter the option");
		option_division = getch();
		
		if (option_division = 'Q' || option_division == 'q' || option_division == '/')
		{
			if (a > b)
			{
				result = a / b;
				printf("Division of a =%d and b = %d gives Quotient= %d \n",a,b, result);
			}
			else
			{
				result = b / a;
				printf("Division of b =%d and a = %d gives Quotient=%d \n",a,b, result);

			}
		}
		else if (option_division = 'R' || option_division == 'r' || option_division == '%')
		{
			if (a > b)
			{
				result = a % b;
				printf("Division of a =%d and b = %d gives remainder=%d \n", a,b,result);
			}
			else
			{
				result = b%a;
				printf("Division of b =%d and a = %d gives remainder=%d \n", a,b,result);

			}
		}
		else
		{
			printf("Invalid character &c entered for division\n");
		}
	}
	else
	{
		printf("Invalid charecter entered for operation\n");
	}


}