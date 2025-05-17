#include<stdio.h>

int main(void)
{
	//if else
	int age;
	printf("enter the age of the voter");
	scanf("%d", &age);

	printf("\n\n");
	if (age > 18) {
		printf("first if block\n");
		printf("ELIGIBLE FOR VOTE/n");
	}
	else {
		printf("first else block\n");
		printf("NOT ELIGIBLE FOR VOTE\n");
	}
	return(0);

}