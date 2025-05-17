#include <stdio.h>


struct MyData {
    int i;
    float f;
    char c;
};
struct MyData data1, data2, data3;

int main(void) {



    data1.i = 10;
    data1.f = 3.14f;
    data1.c = 'A';

    data2.i = 20;
    data2.f = 6.28f;
    data2.c = 'B';

    data3.i = 30;
    data3.f = 9.42f;
    data3.c = 'C';


    printf("Data1: i = %d, f = %.2f, c = %c\n", data1.i, data1.f, data1.c);
    printf("Data2: i = %d, f = %.2f, c = %c\n", data2.i, data2.f, data2.c);
    printf("Data3: i = %d, f = %.2f, c = %c\n", data3.i, data3.f, data3.c);

    return 0;
}
