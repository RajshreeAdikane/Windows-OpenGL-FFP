#include<stdio.h>

int main(void) {
	//ternary operator code
	int a_RKA, b_RKA;
	int c_RKA, d_RKA;
	char result1_RKA;
	char result2_RKA;
	int i_result1_RKA;
	int i_result2_RKA;

	//code
	printf("\n\n");
	a_RKA = 16;
	b_RKA = 14;

	result1_RKA = (a_RKA > b_RKA) ? 'A' : 'B';
	i_result1_RKA = (a_RKA > b_RKA) ? a_RKA : b_RKA;

	printf("the ternary operator are %c and %d\n", result1_RKA, i_result1_RKA);

	printf("\n");
	c_RKA = 12;
	d_RKA = 12;

	result2_RKA = (c_RKA != d_RKA) ? 'A' : 'B';
	i_result2_RKA = (c_RKA != d_RKA) ? c_RKA : c_RKA;

	printf("The result of the second ternary operator is %c and %d\n", result2_RKA, i_result2_RKA);




	return (0);
}