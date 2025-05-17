#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int num;
    int sum = 0;

    // Check if no numbers are provided
    if (argc == 1) {
        printf("\n\n");
        printf("Numbers not given\n");
        exit(0);
    }

    // This program adds command-line arguments given in int form and outputs the sum.
    // Because of atoi(), all command-line arguments other than integers are ignored.

    printf("\n\n");
    printf("Sum of all integer arguments is:\n");

    for (int i = 1; i < argc; i++) {
        num = atoi(argv[i]); // Convert argument to integer
        sum += num;          // Add to sum
    }

    printf("Sum = %d\n\n", sum);
    return(0); // Corrected typo here
}
