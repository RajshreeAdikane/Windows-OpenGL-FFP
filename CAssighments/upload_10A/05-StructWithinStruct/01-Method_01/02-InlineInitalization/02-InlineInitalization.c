#include <stdio.h>
#include <stdlib.h> 

struct Rectangle {
    struct MyPoint {
        int x;
        int y;
    } point_01, point_02;
} rect = { {2, 3}, {5, 6} }; 
int main(void) {

    int width = abs(rect.point_02.x - rect.point_01.x);
    int height = abs(rect.point_02.y - rect.point_01.y);
    int area = width * height;
    int perimeter = 2 * (width + height);

    printf("\nRectangle Properties:\n");
    printf("Point 01: (%d, %d)\n", rect.point_01.x, rect.point_01.y);
    printf("Point 02: (%d, %d)\n", rect.point_02.x, rect.point_02.y);
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);
    printf("Area: %d\n", area);
    printf("Perimeter: %d\n", perimeter);

    return 0;
}
