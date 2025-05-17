#include<stdio.h>

#define MAX_STRING_LENGTH 512

// Function prototypes
void Mystrcpy(char str_des[], char str_sou[]);
int My_strlen(char str[]);
void Mystrrev(char str[]);

int main(void)
{
    char Array[MAX_STRING_LENGTH];
    char Array_copy[MAX_STRING_LENGTH];
    int isStringlength = 0;

    printf("\n\n");
    printf("Enter a string: \n\n");
    gets_s(Array, MAX_STRING_LENGTH);


    Mystrcpy(Array_copy, Array);

    printf("\n\n");
    printf("Original string entered by you is: %s\n\n", Array);

    isStringlength = My_strlen(Array);
    printf("Length of the string is: %d\n\n", isStringlength);

    Mystrrev(Array);
    printf("Reversed string is: %s\n\n", Array);

    // Display the copied string
    printf("Copied string is: %s\n\n", Array_copy);

    return 0;
}

// User-defined function to copy a string
void Mystrcpy(char str_des[], char str_sou[])
{
    int str_length = My_strlen(str_sou);

    for (int i = 0; i < str_length; i++)
    {
        str_des[i] = str_sou[i];
    }
    str_des[str_length] = '\0';
}

int My_strlen(char str[])
{
    int str_length = 0;
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        if (str[i] == '\0')
            break;
        else
            str_length++;
    }
    return str_length;
}

void Mystrrev(char str[])
{
    int start = 0;
    int end = My_strlen(str) - 1;
    char temp;

    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        start++;
        end--;
    }
}
