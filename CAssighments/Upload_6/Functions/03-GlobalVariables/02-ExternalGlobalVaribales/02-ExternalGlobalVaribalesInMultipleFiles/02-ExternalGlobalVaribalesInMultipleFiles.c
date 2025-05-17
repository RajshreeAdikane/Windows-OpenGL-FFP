#include<stdio.h>

int global_count = 0;

int main(void)
{

	void change_count_one(void);
	void change_count_two(void);
	void change_count_three(void);

	printf("\n\n");
	change_count_one();
	change_count_two();
	change_count_three();

	return(0);

}

void change_count_one(void)
{
	global_count = 5;
	printf("global count change one: %d\n", global_count);
}

