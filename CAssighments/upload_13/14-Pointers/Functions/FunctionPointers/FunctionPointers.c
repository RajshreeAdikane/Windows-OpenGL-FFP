#include<stdio.h>

int main(void)
{
	int AddInt(int, int);
	int subInt(int, int);
	float Addfloat(float, float);

	typedef int (*AddIntsFnptr)(int, int);
	AddIntsFnptr ptrAddTwoInt = NULL;
	AddIntsFnptr ptrFuc = NULL;

	typedef float (*AddFloatFnPtr)(float, float);
	AddFloatFnPtr ptrAddTwoFloat = NULL;

	int int_ans = 0;
	float float_ans = 0.0f;

	ptrAddTwoInt = AddInt;
	int_ans = ptrAddTwoInt(67, 89);
	printf("\n\n");
	printf("sum of Int:%d\n\n", int_ans);

	ptrFuc = subInt;
	int_ans = ptrFuc(98, 455);
	printf("\n\n");
	printf("Subtraction of Int:%d\n\n", int_ans);


	ptrAddTwoFloat = Addfloat;
	float_ans = ptrAddTwoFloat(19.34f, 78.98f);
	printf("\n\n");
	printf("sum of float:%f\n\n", float_ans);

	return 0;




}

int AddInt(int a, int b)
{
	int c;
	c = a + b;
	return(c);
}

int subInt(int a, int b)
{
	int c;
	if (a > b)
		c = a - b;
	else
		c = b - a;

	return(c);
}

float Addfloat(float a, float b)
{
	float c;
	c = a + b;
	return(c);
}