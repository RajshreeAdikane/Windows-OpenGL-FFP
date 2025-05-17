#include <stdio.h>
#include <string.h> 

struct MyPoint {
    int x;
    int y;
};


struct MyPointProperties {
    int quadrant;
    char axis_location[10];
};

struct MyPoint point;
struct MyPointProperties point_properties;

int main(void) {
    printf("\n\n");
    printf("Enter the x-coordinate:\n");
    scanf("%d", &point.x);

    printf("Enter the y-coordinate:\n");
    scanf("%d", &point.y);

    printf("\nThe x and y coordinates are: %d and %d\n", point.x, point.y);

    if (point.x == 0 && point.y == 0) {
        printf("The point lies on the origin.\n");
    }
    else {
        if (point.x == 0) {
            if (point.y < 0)
                strcpy(point_properties.axis_location, "Negative Y");
            else if (point.y > 0)
                strcpy(point_properties.axis_location, "Positive Y");

            point_properties.quadrant = 0;
            printf("The point lies on the %s axis.\n\n", point_properties.axis_location);
        }
        else if (point.y == 0) {
            if (point.x < 0)
                strcpy(point_properties.axis_location, "Negative X");
            else if (point.x > 0)
                strcpy(point_properties.axis_location, "Positive X");

            point_properties.quadrant = 0;
            printf("The point lies on the %s axis.\n\n", point_properties.axis_location);
        }
        else {
            point_properties.axis_location[0] = '\0';

            if (point.x > 0 && point.y > 0)
                point_properties.quadrant = 1;
            else if (point.x < 0 && point.y > 0)
                point_properties.quadrant = 2;
            else if (point.x < 0 && point.y < 0)
                point_properties.quadrant = 3;
            else
                point_properties.quadrant = 4;

            printf("The point lies in Quadrant %d.\n\n", point_properties.quadrant);
        }
    }

    return 0;
}
