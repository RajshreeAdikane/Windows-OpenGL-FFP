#include<stdio.h>

int main(void)
{
	char ch;
	char* ptr = NULL;

	ch = 'J';
	printf("\n\n");
	printf("*****BEFORE ptr = &ch*****\n");

	printf("value of ch  = %c\n\n", ch);
	printf("Address of ch  = %p\n\n", &ch);
	printf("Value at adress of ch  = %c\n\n", *(&ch));

	//Assigh add or ch to ptr

	ptr = &ch;

	printf("*****AFTER ptr = &ch*****\n");
	printf("value of ch = %c\n\n", ch);
	printf("Address of ch = %p\n\n", ptr);
	printf("Value at adress of ch  = %c\n\n", *ptr);

	return 0;

}