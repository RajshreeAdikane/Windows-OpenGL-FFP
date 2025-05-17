#include<stdio.h>

extern int global_count;

void change_count_two(void)
{
	global_count = global_count + 10;
	printf("global count change two: %d\n", global_count);
}