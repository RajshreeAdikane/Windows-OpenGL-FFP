#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    char Array[MAX_STRING_LENGTH];
    int str_length;
    int space_count = 0;
    int word_count = 0;



    printf("\n\n");
    printf("Enter a string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);


    str_length = strlen(Array);

    for (int i = 0; i < str_length; i++)
    {
        switch(Array[i])
        {
        case 32: //ASCII valuse for space
            space_count++;
            break;
        default:
            break;

           
        }
    }
    word_count = space_count+1;


    printf("\n\n");
    printf("String entered by you is: %s\n\n", Array);

    printf("Number of spaces in the string = %d\n\n", space_count);
    printf("Number of word in the string = %d\n\n", word_count);

    return 0;
}
