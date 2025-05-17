#include <stdio.h>
#include <string.h>
#include <ctype.h> // For toupper() function

#define MAX_STRING_LENGTH 512

int main(void)
{
    char Array[MAX_STRING_LENGTH];
    char Array_Capitalized[MAX_STRING_LENGTH];
    int str_length;

    printf("\n\n");
    printf("Enter a string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);

    str_length = strlen(Array);

    int j = 0;
    for (int i = 0; i < str_length; i++)
    {

        if (i == 0 || Array[i - 1] == ' ')
        {
            Array_Capitalized[j] = toupper(Array[i]);
        }
        else
        {
            Array_Capitalized[j] = Array[i];
        }
        j++;
    }
    Array_Capitalized[j] = '\0';

    printf("\n\n");
    printf("String entered by you is: %s\n\n", Array);
    printf("String after capitalizing the first letter of every word: %s\n\n", Array_Capitalized);

    return 0;
}
