#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    char Array[MAX_STRING_LENGTH];
    char Array_Captilized[MAX_STRING_LENGTH];
    int str_length;



    printf("\n\n");
    printf("Enter a string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);


    str_length = strlen(Array);

    for (int i = 0, j=0; i < str_length; i++)
    {
        if (i == 0) {
            Array_Captilized[j] = toupper(Array[i]);
        else if (Array[i] == ' ')
            Array_Captilized[j + 1] = toupper(Array[i + 1])
            i++;
            j++;

        }
        else
            Array_Captilized[j] = Array[i];



    }
    Array_Captilized[strlen(Array_Captilized)] = '\0';



    printf("\n\n");
    printf("String entered by you is: %s\n\n", Array);

    printf("String after Every first word capilaize = %s\n\n", Array_Captilized);

    return 0;
}
