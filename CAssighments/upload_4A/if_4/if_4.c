#include<stdio.h>
int main(void)
{
	//code of age
	printf("\n\n");
	int age;
	printf("your age is :\n\n");
	scanf("%d", &age);

	if (age >=18) {
		printf("Eligible for vote\n\n");
	}
	printf("Not eligible for vote\n\n");
	return(0);
}