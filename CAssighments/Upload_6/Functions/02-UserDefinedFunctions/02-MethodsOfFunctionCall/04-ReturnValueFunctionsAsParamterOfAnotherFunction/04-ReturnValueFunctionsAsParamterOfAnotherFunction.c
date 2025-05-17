#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int Addition(int a, int b);

	int result, a1, b1, c1, d1;

	a1 = 30;
	b1 = 20;
	c1 = 40;
	d1 = 50;

	result = Addition(Addition(a1, b1), Addition(c1, b1));

	printf("\n\n");
	printf(" % d + % d + % d + % d = % d\n", a1, b1, c1, d1, result);

	//Addition()
	return(0);

}

int Addition(int a, int b)
{
	int sum;
	sum = a + b;
	return(sum);
}