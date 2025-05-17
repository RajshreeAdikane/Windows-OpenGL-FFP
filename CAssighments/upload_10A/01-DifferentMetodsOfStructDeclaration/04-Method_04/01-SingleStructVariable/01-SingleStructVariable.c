#include <stdio.h>

// Define struct
struct MyData {
    int i;
    float f;
    double d;
    char c;
};

int main(void) {

    struct MyData data;

    int i_size;
    int f_size;
    int d_size;
    int struct_MyData_size;

    data.i = 30;
    data.f = 12.34f;
    data.d = 1.2999;
    data.c = 'A';


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
