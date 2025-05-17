#include <stdio.h>
#include<conio.h>

// Define struct
struct MyData {
    int i;
    float f;
    double d;
    char ch;
};

int main(void) {
    
    struct MyData data;

    printf("\n\n");

    printf("Enter a Integer value for struct:\n");
    scanf("%d", &data.i);

    printf("Enter a float value for struct:\n");
    scanf("%f", &data.f);

    printf("Enter a Double value for struct:\n");
    scanf("%lf", &data.d);

    printf("Enter a Charactr for struct:\n");
    data.ch = getch();

    printf("Sizes in bytes of data struct members:\n");
    printf(" i = %d bytes\n", (data.i));
    printf(" f = %f bytes\n", (data.f));
    printf(" d = %lf bytes\n", (data.d));
    printf(" c = %c bytes\n", (data.ch));

    return 0;
}
