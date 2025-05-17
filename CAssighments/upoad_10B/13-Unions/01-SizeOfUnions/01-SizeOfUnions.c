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

	printf("\n\n");
	printf("the size of MyStruct: = %zu\n\n", sizeof(s));
	printf("The size of MyUnion: = %zu\n\n", sizeof(u));

	return 0;

}