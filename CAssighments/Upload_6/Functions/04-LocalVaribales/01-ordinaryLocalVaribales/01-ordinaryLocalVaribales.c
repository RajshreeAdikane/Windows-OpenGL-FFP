#include<stdio.h>

int main(void)
{
	int a = 5;
	printf("\n");
	printf("A=%d\n", a);

	void change_count(void);

	change_count();
	change_count();
	change_count();

	return 0;


}
void change_count(void)
{
	static int local_count = 0;
	local_count = local_count + 1;
	printf("local count = %d\n\n", local_count);
}