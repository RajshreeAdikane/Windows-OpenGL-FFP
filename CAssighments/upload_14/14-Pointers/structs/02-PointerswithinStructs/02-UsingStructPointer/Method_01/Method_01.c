#include <stdio.h>
#include <stdlib.h>

struct Data {
    int* intVal;
    int i;

    float* floatVal;
    float f;

    double* doubleVal;
    double d;
};

int main(void) {
    struct Data* data = (struct Data*)malloc(sizeof(struct Data));
    if (data == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    (*data).i = 12;
    (*data).intVal = &((*data).i);

    (*data).f = 11.11f;
    (*data).floatVal = &((*data).f);

    (*data).d = 12.234566;
    (*data).doubleVal = &((*data).d);

    printf("intVal (via pointer): %d\n", *((*data).intVal));
    printf("intVal address: %p\n\n", (*data).intVal);

    printf("floatVal (via pointer): %f\n", *((*data).floatVal));
    printf("floatVal address: %p\n\n", (*data).floatVal);

    printf("doubleVal (via pointer): %lf\n", *((*data).doubleVal));
    printf("doubleVal address: %p\n\n", (*data).doubleVal);

    free(data);
    data = NULL;

    printf("Memory freed\n");

    return 0;
}
