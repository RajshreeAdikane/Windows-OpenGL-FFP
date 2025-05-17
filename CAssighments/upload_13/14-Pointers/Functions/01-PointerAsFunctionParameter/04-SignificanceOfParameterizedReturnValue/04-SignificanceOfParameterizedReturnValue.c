#include<stdio.h>

enum
{
	NEGATIVE = - 1,
	ZERO,
	POSITIVE,
};

int main(void)
{
	int Diffrence(int, int, int *);
	int a, b;
	int ans;
	int ret;

	printf("\n\n");
	printf("Enter the value of A:");
	scanf("%d", &a);
	printf("Enter the value of B:");
	scanf("%d", &b);

	ret = Diffrence(a, b, &ans);
	printf("diff of %d and %d is %d\n\n", a, b, ans);

	if (ret == POSITIVE)
	{
		printf("diff of %d and %d positive\n\n", a, b);
	}
	else if (ret == NEGATIVE)
	{
		printf("diff of %d and %d negative\n\n", a, b);
	}
	else
	{
		printf("diff of %d and %d zero\n\n", a, b);
	}


	return 0;


}

int Diffrence(int x, int y, int* diff)
{
	*diff = x - y;
	if (*diff > 0)
	{
		return (POSITIVE);
	}
	else if (*diff < 0)
	{
		return(NEGATIVE);
	}
	else
	{
		return(ZERO);
	}

}