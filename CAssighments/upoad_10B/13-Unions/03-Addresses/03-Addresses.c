#include<stdio.h>

struct MyStruct
{
	int i;
	float f;
	double d;
	char c;
};


union MyUnion
{
	int i;
	float f;
	double d;
	char c;
};

int main(void)
{
	struct MyStruct s;
	union MyUnion u;

	printf("\n");
	printf("the members of Struct are: \n");
	s.i = 12;
	s.f = 89.76;
	s.d = 1.234;
	s.c = 'J';

	printf("s.i = %d\n", s.i);
	printf("s.f = %f\n", s.f);
	printf("s.d = %lf\n", s.d);
	printf("s.c = %c\n\n", s.c);

	printf("the Address of Struct are: \n");
	printf("s.i = %p\n", &s.i);
	printf("s.f = %p\n", &s.f);
	printf("s.d = %p\n", &s.d);
	printf("s.c = %p\n\n", &s.c);

	printf("Adress of Struct = %p\n", &s);

	printf("\n\n");

	printf("Members of Union are: \n");

	u.i = 13;
	printf("u.i = %d\n", u.i);

	u.f = 90.78;
	printf("u.f = %f\n", u.f);

	u.d = 4.567;
	printf("u.d = %lf\n", u.d);

	u.c = 'A';
	printf("u.c = %c\n\n", u.c);

	printf("the Address of Union are: \n");
	printf("u.i = %p\n", &u.i);
	printf("u.f = %p\n", &u.f);
	printf("u.d = %p\n", &u.d);
	printf("u.c = %p\n\n", &u.c);

	printf("Adress of Union = %p\n\n", &u);


	return 0;

}