#include<stdio.h>

struct Employee
{
    char name[100];
    int age;
    float salary;
    char sex;
    char marital_status;
};

int main(void)
{
    printf("\n\n");
    printf("Sizes of data types and pointers:\n\n");
    printf("Size of int: %zu \t\t\t Size of pointer to int* :%zu \t\t\t Size of pointer to int (int**): %zu\n", sizeof(int), sizeof(int*), sizeof(int**));
    printf("Size of float: %zu \t\t\t Size of pointer to float* :%zu \t\t\t Size of pointer to float (float**): %zu\n", sizeof(float), sizeof(float*), sizeof(float**));
    printf("Size of double: %zu \t\t\t Size of pointer to double* :%zu \t\t\t Size of pointer to double (double**): %zu\n", sizeof(double), sizeof(double*), sizeof(double**));
    printf("Size of char: %zu \t\t\t Size of pointer to char* :%zu \t\t\t Size of pointer to char (char**): %zu\n", sizeof(char), sizeof(char*), sizeof(char**));
    printf("Size of struct Employee: %zu \t\t\t Size of pointer to struct Employee* :%zu \t\t\t Size of pointer to struct Employee (struct Employee**): %zu\n\n", sizeof(struct Employee), sizeof(struct Employee*), sizeof(struct Employee**));

    return 0;
}
