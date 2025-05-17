#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	int MyAdd(int x, int y);

	int result, a1, b1, c1, d1;

	a1 = 100;
	b1 = 200;
	c1 = 400;
	d1 = 500;

	printf("\n\n");
	printf(" % d + % d + % d + % d = % d\n", a1, b1, c1, d1, MyAdd(MyAdd(a1,b1), MyAdd(c1,d1)));

	//Addition()
	return(0);

}
int MyAdd(int x, int y)
{
	int Addition(int , int );
	return(Addition(x, y));
}
int Addition(int a, int b)
{
	return(a+b);
}