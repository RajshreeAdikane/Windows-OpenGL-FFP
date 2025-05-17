#include<stdio.h>
#include<conio.h>

int main(void)
{
	//using switch case for mathatical oprations
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

	switch (option)
	{
	case 'A':
	case 'a':
		result = a + b;
		printf("Addition of a = %d and b= %d\n gives result =%d \n", a, b, result);
			break;

	case 'S':
	case 's':
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
		break;

	case 'M':
	case 'm':
		result = a * b;
		printf("multiplication of a =%d and b=%d gives result = %d\n", a, b, result);
		break;

	case 'D':
	case 'd':
		printf("Enter the option in character:\n");
		printf("'Q' or 'q' or '/' for Quotient upon Divivon\n");
		printf("'R' or 'r' or '%' for Remainder upon Divivon\n");

		printf("Enter the option");
		option_division = getch();

		switch (option_division)
		{
		case 'Q':
		case 'q':
		case '/':
			if (a > b)
			{
				result = a / b;
				printf("Division of a =%d and b = %d gives Quotient= %d \n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Division of b =%d and a = %d gives Quotient=%d \n", a, b, result);

			}
			break;


		case 'R':
		case 'r':
		case '%':
			if (a > b)
			{
				result = a % b;
				printf("Division of a =%d and b = %d gives remainder=%d \n", a, b, result);
			}
			else
			{
				result = b % a;
				printf("Division of b =%d and a = %d gives remainder=%d \n", a, b, result);

			}
			break;
		default:
			printf("Entered the INVALID character for division %c\n", option_division);
			break;
		}
		break;
	default:
		printf("Invalid charecter Entered%c\n",option);
		break;
	}
	return(0);
}
