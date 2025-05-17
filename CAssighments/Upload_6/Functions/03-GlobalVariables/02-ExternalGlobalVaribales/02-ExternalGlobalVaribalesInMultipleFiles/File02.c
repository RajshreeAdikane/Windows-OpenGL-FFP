#include<stdio.h>

extern int global_count;

void change_count_three(void)
{
	global_count = global_count + 20;
	printf("global count change three: %d\n", global_count);
}