# include<stdio.h>

int main(void)
{

	int RKA_num, RKA_num1;

	printf("\n\n");

	printf("Enter any RKA_number");
	scanf("%d", &RKA_num);

	printf("Enter the digits you want to print from %d Onwards", RKA_num);
	scanf("%d", &RKA_num1);

	printf("printing digits %d to %d\n\n", RKA_num, RKA_num1);

	for (int i = RKA_num; i <= (RKA_num + RKA_num1); i++)
	{
		printf("\t%d\n", i);
	}
	return(0);

}