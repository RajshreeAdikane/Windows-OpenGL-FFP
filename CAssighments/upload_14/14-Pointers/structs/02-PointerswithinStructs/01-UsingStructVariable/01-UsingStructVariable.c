#include <stdio.h>

struct Data {
    int* intVal;
    int i;

    float* floatVal;
    float f;

    double* doubleVal;
    double d;
};

int main(void) {
    struct Data data;

    data.i = 12;
    data.intVal = &data.i;

    data.f = 11.11f;
    data.floatVal = &data.f;

    data.d = 12.234566;
    data.doubleVal = &data.d;

    printf("\n\n");

    printf("intVal (via pointer): %d\n", *data.intVal);
    printf("intVal address: %p\n\n", data.intVal);

    printf("floatVal (via pointer): %f\n", *data.floatVal);
    printf("floatVal address: %p\n\n", data.floatVal);

    printf("doubleVal (via pointer): %f\n", *data.doubleVal);
    printf("doubleVal address: %p\n\n", data.doubleVal);

    return 0;
}
