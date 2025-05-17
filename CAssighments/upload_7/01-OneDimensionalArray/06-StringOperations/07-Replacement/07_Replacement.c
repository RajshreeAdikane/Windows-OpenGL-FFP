#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    void ReplaceVowels(char[]);

    char Array[MAX_STRING_LENGTH];
    //char Array_cpy[MAX_STRING_LENGTH];
    //int vowel_count = 0;

    printf("\n\n");
    printf("Enter a string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);


    printf("\n\n");
    printf("String entered by you is: %s\n\n", Array);

    //strcpy(Array, Array_cpy);

    ReplaceVowels(Array);

    printf("The Replaced String is: %s\n\n", Array);

    return 0;
}

void ReplaceVowels(char str[])
{
    //int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' ||
            str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            //count++;
            str[i] = '*';
        }
    }
}
