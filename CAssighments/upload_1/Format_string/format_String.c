#include <stdio.h>

int main(void)
{
	//code
	printf("\n\n");
	int RKA_a = 13;
	printf("Integer Decimal value of 'RKA_a' = %d\n", RKA_a);
	printf("Integer Octal Value of 'RKA_A' = %o\n", RKA_a);
	printf("Interger Hexadecimal value of 'RKA_A' hexadecimal value in lower case = %x\n", RKA_a);
	printf("Integer Hexadecimal value of 'RKA_A' hexadecimal value in upper case = %X\n", RKA_a);

	char ch = 'RKA';
	printf("character ch = %c\n", ch);

	char str[] = "Rajashree Adikane Roll no 20 in RTR6 2024 batch";
	printf("string str = %s\n", str);

	long RKA = 12345L;
	printf("long integer = %ld\n", RKA);

	unsigned int RKA_b = 12;
	printf("unsigned interger 'RKA_b' = %u\n", RKA_b);

	float f_RKA = 12.12;
	printf("floating point number with %%f of 'f_RKA' = %f \n ", f_RKA);
	printf("floating point number with %%4.5f of 'f_RKA' = %4.5f\n", f_RKA);
	printf("floating point number with %%6.5f of 'f_RKA' = %6.5f\n", f_RKA);

	double RKA_pi = 3.141578980909;
	printf("Double prcision floating point number without exponential of 'RKA_pi' = %g\n", RKA_pi);
	printf("Double prcision floating point number with exponential (lower case) of 'RKA_pi' = %e\n", RKA_pi);
	printf("Double prcision floating point number wit exponential(upper case) of 'RKA_pi' = %E\n", RKA_pi);
	printf("Double hexadeccimal value of 'RKA_pi' in lower case  = %a\n", RKA_pi);
	printf("Double hexadeccimal value of 'RKA_pi' in upper case  = %A\n", RKA_pi);

	printf("\n\n");

	return(0);



}