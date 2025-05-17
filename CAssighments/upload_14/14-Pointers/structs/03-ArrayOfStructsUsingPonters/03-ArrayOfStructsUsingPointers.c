#include <stdio.h>
#include <stdlib.h>

#define NAME_LENGTH 100
#define MARITAL_STATUS_LENGTH 10

struct employee {
    char name[NAME_LENGTH];
    int age;
    char sex;
    float salary;
    char marital_status[MARITAL_STATUS_LENGTH];
};

int main() {
    int num_employee, i;

    printf("Enter the number of employees: ");
    scanf("%d", &num_employee);

    struct employee* employees = (struct employee*)malloc(num_employee * sizeof(struct employee));
    if (employees == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (i = 0; i < num_employee; i++) {
        printf("\nEnter details for employee %d:\n", i + 1);

        printf("Name: ");
        scanf(" %99s", employees[i].name);

        printf("Age: ");
        scanf("%d", &employees[i].age);

        printf("Sex (M/F): ");
        scanf(" %c", &employees[i].sex);

        printf("Salary: ");
        scanf("%f", &employees[i].salary);

        printf("Marital Status (Single/Married): ");
        scanf(" %9s", employees[i].marital_status);
    }

    printf("\nEmployee Details:\n");
    for (i = 0; i < num_employee; i++) {
        printf("\nEmployee %d:\n", i + 1);
        printf("Name: %s\n", employees[i].name);
        printf("Age: %d\n", employees[i].age);
        printf("Sex: %c\n", employees[i].sex);
        printf("Salary: %.2f\n", employees[i].salary);
        printf("Marital Status: %s\n", employees[i].marital_status);
    }

    free(employees);

    return 0;
}
