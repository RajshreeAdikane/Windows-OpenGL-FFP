#include<stdio.h>


int main(void)
{

	extern int global_count; // extern the global variable in a single file

	void change_count_one(void);
	void change_count_two(void);
	void change_count_three(void);

	printf("\n\n");
	change_count_one();
	change_count_two();
	change_count_three();

	return(0);

}
int global_count = 0;

void change_count_one(void)
{
	global_count = 5;
	printf("global count change one: %d\n", global_count);
}
void change_count_two(void)
{
	global_count = global_count + 10;
	printf("global count change two: %d\n", global_count);
}
void change_count_three(void)
{
	global_count = global_count + 20;
	printf("global count change three: %d\n", global_count);
}