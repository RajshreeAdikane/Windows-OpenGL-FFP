#include <stdio.h>

int main(void) {
    struct MyData {
        int i;
        float f;
        double d;
        char c;
    };
    struct MyData data_one = { 30, 12.34f, 2.344, 'A' };
    struct MyData data_two = { 82, 12.34f, 2.344, 68 };
    struct MyData data_three = { 45, 0.0f, 0.0, 'J' };
    struct MyData data_four = { 69, 0.0f, 0.0, '\0' };

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
