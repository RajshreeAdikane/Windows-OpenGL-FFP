#include <stdio.h>

int main(void) {
    struct MyData {
        int i;
        float f;
        double d;
        char c;
    };

    struct MyData data_one, data_two, data_three, data_four;

    printf("\n\nEnter values for data_one:\n");
    printf("Enter integer: ");
    scanf("%d", &data_one.i);
    printf("Enter float: ");
    scanf("%f", &data_one.f);
    printf("Enter double: ");
    scanf("%lf", &data_one.d);
    printf("Enter char: ");
    scanf(" %c", &data_one.c);

    printf("\n\nEnter values for data_two:\n");
    printf("Enter integer: ");
    scanf("%d", &data_two.i);
    printf("Enter float: ");
    scanf("%f", &data_two.f);
    printf("Enter double: ");
    scanf("%lf", &data_two.d);
    printf("Enter char: ");
    scanf(" %c", &data_two.c);

    printf("\n\nEnter values for data_three:\n");
    printf("Enter integer: ");
    scanf("%d", &data_three.i);
    printf("Enter float: ");
    scanf("%f", &data_three.f);
    printf("Enter double: ");
    scanf("%lf", &data_three.d);
    printf("Enter char: ");
    scanf(" %c", &data_three.c);

    printf("\n\nEnter values for data_four:\n");
    printf("Enter integer: ");
    scanf("%d", &data_four.i);
    printf("Enter float: ");
    scanf("%f", &data_four.f);
    printf("Enter double: ");
    scanf("%lf", &data_four.d);
    printf("Enter char: ");
    scanf(" %c", &data_four.c);

    printf("\n\n");
    printf("Sizes in bytes of data struct members:\n");
    printf("Size of i = %zu bytes\n", sizeof(data_one.i));
    printf("Size of f = %zu bytes\n", sizeof(data_one.f));
    printf("Size of d = %zu bytes\n", sizeof(data_one.d));
    printf("Size of c = %zu bytes\n", sizeof(data_one.c));

    printf("\n\n");
    printf("The size of struct MyData: %zu bytes\n", sizeof(struct MyData));

    printf("\n\n");
    printf("Values of data_one: i = %d, f = %.2f, d = %.3f, c = %c\n", data_one.i, data_one.f, data_one.d, data_one.c);
    printf("Values of data_two: i = %d, f = %.2f, d = %.3f, c = %c\n", data_two.i, data_two.f, data_two.d, data_two.c);
    printf("Values of data_three: i = %d, f = %.2f, d = %.3f, c = %c\n", data_three.i, data_three.f, data_three.d, data_three.c);
    printf("Values of data_four: i = %d, f = %.2f, d = %.3f, c = %c\n", data_four.i, data_four.f, data_four.d, data_four.c);

    return 0;
}
