#include<stdio.h>


union MyUnion
{
	int i;
	float f;
	double d;
	char c;
};

int main(void)
{
	union MyUnion u1,u2;

	printf("\n");
	printf("the members of u1 are: \n");
	u1.i = 122;
	u1.f = 78.34;
	u1.d = 2.6783;
	u1.c = 'R';

	printf("u1.i = %d\n", u1.i);
	printf("u1.f = %f\n", u1.f);
	printf("u1.d = %lf\n", u1.d);
	printf("u1.c = %c\n\n", u1.c);

	printf("the Address of u1.are: \n");
	printf("u1.i = %p\n", &u1.i);
	printf("u1.f = %p\n", &u1.f);
	printf("u1.d = %p\n", &u1.d);
	printf("u1.c = %p\n\n", &u1.c);

	printf("Adress of u1 union = %p\n", &u1);

	printf("\n\n");

	printf("Members of u2 are: \n");

	u2.i = 45;
	printf("u2.i = %d\n", u2.i);

	u2.f = 12.34;
	printf("u2.f = %f\n", u2.f);

	u2.d = 6.545;
	printf("u2.d = %lf\n", u2.d);

	u2.c = 'A';
	printf("u2.c = %c\n\n", u2.c);

	printf("the Address of u2 are: \n");
	printf("u2.i = %p\n", &u2.i);
	printf("u2.f = %p\n", &u2.f);
	printf("u2.d = %p\n", &u2.d);
	printf("u2.c = %p\n\n", &u2.c);

	printf("Adress of u2 union = %p\n\n", &u2);


	return 0;

}