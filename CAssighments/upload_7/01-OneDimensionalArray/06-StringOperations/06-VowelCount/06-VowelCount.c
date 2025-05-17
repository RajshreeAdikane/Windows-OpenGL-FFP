#include <stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    int CountVowels(char str[]);

    char Array[MAX_STRING_LENGTH];
    int vowel_count = 0;

    printf("\n\n");
    printf("Enter a string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);

    printf("\n\n");
    printf("String entered by you is: %s\n\n", Array);

    vowel_count = CountVowels(Array);

    printf("The number of vowels in the string is: %d\n\n", vowel_count);

    return 0;
}

int CountVowels(char str[])
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' ||
            str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            count++;
        }
    }
    return count;
}
