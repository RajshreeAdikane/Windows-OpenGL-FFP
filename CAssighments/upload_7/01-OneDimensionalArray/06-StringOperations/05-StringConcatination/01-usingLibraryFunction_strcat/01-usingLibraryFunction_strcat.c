#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    char Array[MAX_STRING_LENGTH];
    char Array_1[MAX_STRING_LENGTH];

    printf("\n\n");
    printf("Enter the first string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("Enter the second string: \n\n");
    gets_s(Array_1, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("First string entered by you is: %s\n\n", Array);

    printf("\n\n");
    printf("Second string entered by you is: %s\n\n", Array_1);

    strcat(Array, Array_1);

    printf("The output of the concatenation is: %s\n\n", Array);

    return 0;
}
