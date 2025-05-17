#include <stdio.h>


int main(void) {

    // Define struct
    struct MyData {
        int i;
        float f;
        double d;
        char c;
    } data = { 30, 12.34f, 2.344, 'A' };

    printf("\n\n");
    printf("Sizes in bytes of data struct members:\n");
    printf("Size of i = %zu bytes\n", sizeof(data.i));
    printf("Size of f = %zu bytes\n", sizeof(data.f));
    printf("Size of d = %zu bytes\n", sizeof(data.d));
    printf("Size of c = %zu bytes\n", sizeof(data.c));

    printf("\n\n");
    printf("The size of struct MyData: %zu bytes\n", sizeof(struct MyData));

    return 0;
}
