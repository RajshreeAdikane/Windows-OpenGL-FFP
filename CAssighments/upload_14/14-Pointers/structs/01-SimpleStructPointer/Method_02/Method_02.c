#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int intVal;
    float floatVal;
    double doubleVal;
} Data;  

int main(void) {
    int intval_size;
    int floatVal_size;
    int doubleVal_size;

    Data* pData = NULL; 

    pData = (Data*)malloc(sizeof(Data));
    if (pData == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    else {
        printf("Successfully allocated memory for struct Data.\n\n");
    }

    pData->intVal = 12;
    pData->floatVal = 78.78f;
    pData->doubleVal = 30.123456;

    printf("\n*** Accessing struct members using pointer ***\n");
    printf("intVal: %d\n", pData->intVal);
    printf("floatVal: %f\n", pData->floatVal);
    printf("doubleVal: %lf\n", pData->doubleVal);

    printf("\nSize of struct Data: %zu bytes\n", sizeof(Data));

    printf("\nSize of struct members:\n");
    intval_size = sizeof(pData->intVal);
    floatVal_size = sizeof(pData->floatVal);
    doubleVal_size = sizeof(pData->doubleVal);

    printf("Size of intVal: %d bytes\n", intval_size);
    printf("Size of floatVal: %d bytes\n", floatVal_size);
    printf("Size of doubleVal: %d bytes\n", doubleVal_size);

    if (pData) {
        free(pData);
        pData = NULL;
        printf("\nMemory has been freed.\n");
    }

    return 0;
}
