#include<stdio.h>
#include<stdarg.h>

int main(void)
{

	int CalculateSum(int, ...);

	int ans;

	printf("\n\n");

	ans = CalSum(5, 10, 20, 30, 40, 50);
	printf("ans = %d\n\n", ans);

	ans = CalSum(10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	printf("ans = %d\n\n", ans);

	ans = CalSum(0);
	printf("ans = %d\n\n", ans);


	return 0;

}

int CalSum(int num, ...) //variadic function
{
	int sum = 0;
	int n;

	va_list num_list;

	va_start(num_list, num);

	while (num)	
	{
		n = va_arg(num_list, int);
		sum = sum + n;
		num--;
	}
	va_end(num_list);
	return(sum);

}