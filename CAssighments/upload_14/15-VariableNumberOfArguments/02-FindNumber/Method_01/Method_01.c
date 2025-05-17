#include <stdio.h>
#include <stdarg.h>

#define NUM_TO_BE_FOUND 3
#define NUM_ELEMENTS 10

int FindNum(int num_to_be_found, int num, ...); 

int main(void) {
    printf("\n\n");
    int count = FindNum(NUM_TO_BE_FOUND, NUM_ELEMENTS, 3, 7, 4, 6, 7, 4, 4, 5, 8, 9);

    if (count == 0) {
        printf("Number %d could not be found.\n\n", NUM_TO_BE_FOUND);
    }
    else {
        printf("Number %d was found %d times.\n\n", NUM_TO_BE_FOUND, count);
    }

    return 0;
}

int FindNum(int num_to_be_found, int num, ...) {
    int count = 0; 
    int n;

    va_list num_list;
    va_start(num_list, num);

    while (num > 0) {
        n = va_arg(num_list, int);
        if (n == num_to_be_found) {
            count++;
        }
        num--;
    }

    va_end(num_list);
    return count; 
}
