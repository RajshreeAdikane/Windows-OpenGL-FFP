#include <stdio.h>

int main(void)
{
	//code 
	int num;
	printf("\n\n");
	printf("enter the value of 'num' upto 500 :");
	scanf("%d", &num);

	if (num < 0) {
		printf("the number is less than 0 is negative = %d\n\n", num);
	}
	if ((num > 0) && (num < 100)) {
		printf("number is between 0 to 100 = %d\n\n", num);
	}
	if ((num > 100) && (num < 200)) {
		printf("number is between 100 to 200 = %d\n\n", num);
	}
	if ((num > 200) && (num < 300)) {
		printf("number is between 200 to 300 = %d\n\n", num);
	}
	if ((num > 300) && (num < 400)) {
		printf("number is between 300 to 400 = %d\n\n", num);
	}
	if ((num > 400) && (num < 500)) {
		printf("number is between 400 to 500 = %d\n\n", num);
	}
	return(0);

}