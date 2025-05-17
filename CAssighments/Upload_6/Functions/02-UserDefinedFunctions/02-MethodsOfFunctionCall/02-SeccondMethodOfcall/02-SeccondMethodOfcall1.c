#include<stdio.h>

int main(int argc, char* argv[], char* envp[])
{
	void Display_info(void);

	Display_info();

	return(0);



}
void Display_info(void)
{
    //function prototypes
	void Function_My(void);
	void Function_Name(void);
	void Function_Is(void);
	void Function_FirstName(void);
	void Function_SecondName(void);
	void Function_LastName(void);
	void FUnction_OfAMC(void);

	//function declaration
	Function_My();
	Function_Name();
	Function_Is();
	Function_FirstName();
	Function_SecondName();
	Function_LastName();
	FUnction_OfAMC();

}

void Function_My(void)
{
	printf("\n\n");
	printf("My");
}
void Function_Name(void)
{
	printf("\n\n");
	printf("Name");

}
void Function_Is(void)
{
	printf("\n\n");
	printf("is");

}
void Function_FirstName(void)
{
	printf("\n\n");
	printf("Rajashree");

}
void Function_SecondName(void)
{
	printf("\n\n");
	printf("Kashinath");
}
void Function_LastName(void)
{
	printf("\n\n");
	printf("Adikane");
}
void FUnction_OfAMC(void)
{
	printf("\n\n");
	printf("Student of AMC");
}