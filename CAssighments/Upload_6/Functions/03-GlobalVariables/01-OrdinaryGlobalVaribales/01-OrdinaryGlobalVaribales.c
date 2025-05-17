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
	global_count = 100;
	printf("global count change one: %d\n", global_count);
}
void change_count_two(void)
{
	global_count = global_count+1;
	printf("global count change two: %d\n", global_count);
}
void change_count_three(void)
{
	global_count = global_count + 10;
	printf("global count change three: %d\n", global_count);
}