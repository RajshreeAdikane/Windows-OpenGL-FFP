#include<stdio.h>

int main(void)
{
	//if else
	int a_RKA, b_RKA;
	printf("enter the integer");
	scanf("%d", &a_RKA);

	printf("enter the integer");
	scanf("%d", &b_RKA);

	if (a_RKA > b_RKA) {
		printf("first if block\n");
		printf("a_RKA is greater than b_RKA\n");
	}
	else {
		printf("first else block\n");
		printf("a_RKA is NOT greater than b_RKA\n");
	}
	if (a_RKA == b_RKA) {
		printf("second if block\n");
		printf("a_RKA is EQUAL TO b_RKA\n");
	}
	else {
		printf("second else block\n");
		printf("a_RKA is NOT EQUAL TO b_RKA\n");
	}
	return(0);

}