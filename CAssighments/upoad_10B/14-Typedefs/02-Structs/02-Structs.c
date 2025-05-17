#include <stdio.h>
#include <string.h>

#define MAX_CHAR_LENGTH 100

// Typedef struct for MYData
typedef struct {
    int i;
    float f;
    double d;
    char c;
} MYData;

// Typedef struct for Employee
typedef struct {
    char name[MAX_CHAR_LENGTH];
    unsigned int age;
    char gender;
    double salary;
} Employee;

int main(void) {
    MYData data = { 10, 12.5f, 45.678, 'A' };
    Employee emp;

    printf("\nEnter Employee Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Employee Age: ");
    scanf("%u", &emp.age);
    printf("Enter Employee Gender (M/F): ");
    scanf(" %c", &emp.gender);
    printf("Enter Employee Salary: ");
    scanf("%lf", &emp.salary);

    printf("\nMYData Details:\n");
    printf("Integer: %d\n", data.i);
    printf("Float: %.2f\n", data.f);
    printf("Double: %.3f\n", data.d);
    printf("Character: %c\n", data.c);

    printf("\nEmployee Details:\n");
    printf("Name: %s\n", emp.name);
    printf("Age: %u\n", emp.age);
    printf("Gender: %c\n", emp.gender);
    printf("Salary: %.2lf\n", emp.salary);

    return 0;
}
