#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	void Function_My(void);

	Function_My();

	return(0);



}


void Function_My(void)
{
//function declaration
	void Function_Name(void);
	Function_Name();
	printf("\n\n");
	printf("My");
}
void Function_Name(void)
{
	void Function_Is(void);
	Function_Is();
	printf("\n\n");
	printf("Name");

}
void Function_Is(void)
{
	void Function_FirstName(void);
	Function_FirstName();
	printf("\n\n");
	printf("is");

}
void Function_FirstName(void)
{
	void Function_SecondName(void);
	Function_SecondName();
	printf("\n\n");
	printf("Rajashree");

}
void Function_SecondName(void)
{
	void Function_LastName(void);
	Function_LastName();
	printf("\n\n");
	printf("Kashinath");
}
void Function_LastName(void)
{
	void FUnction_OfAMC(void);
	FUnction_OfAMC();
	printf("\n\n");
	printf("Adikane");
}
void FUnction_OfAMC(void)
{
	printf("\n\n");
	printf("Student of AMC");
}