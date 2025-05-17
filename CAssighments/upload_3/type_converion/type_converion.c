# include<stdio.h>

int main(void)
{
	int a, b;
	char char_1, char_2;

	int i, result_int;
	float f, result_float;

	//Implicit Type conversion of int and char
	printf("\n\n");
	printf("enter the value of interger a = ");
	scanf("%d", &a);
	char_1 = a;

	printf("a = %d\n\n", a);
	printf("char_1 = %c\n\n", char_1);

	printf("\n\n");
	printf("enter the character of char_2 = ");
	scanf(" %c", &char_2);
	b = char_2;
	printf("char_2 = %c\n\n", char_2);
	printf("b = %d\n\n", b);*/

	Implicit conversion of int and float
	printf("\n\n");
	i = 12;
	f = 12.5f;
	result_float = i + f;
	printf("adding int i =%d  and float f %f gives floating point sum = %f ", i, f, result_float);

	printf("\n\n");
	result_int = i + f;
	printf("adding int i =%d  and float f %f gives floating point sum = %d ", i, f, result_int);


	//Explicit conversion

	printf("\n\n");
	f = 12.34;
	i = (int)f;
	printf("i = %d\n", i);
	printf("%f\n", f);
	
	return(0);
}