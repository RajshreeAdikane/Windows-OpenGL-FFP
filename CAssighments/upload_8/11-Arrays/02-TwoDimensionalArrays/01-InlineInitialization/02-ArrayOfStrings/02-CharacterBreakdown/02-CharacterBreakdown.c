#include <stdio.h>

#define MAX_STRING_LENGTH 512

int Mystrlen(char str[]);

int main(void)
{
    char Array_str[10][15] = { "Hello!", "Welcome", "To", "AMC", "Rajashree", "Kashinath", "Adikane", "2024", "Roll_no", "020" };
    int isStrLength[10]; 
    int char_Size;
    int Array_str_size;
    int Array_str_num_ele, Array_str_num_rows, Array_str_num_col;

    printf("\n\n");

    char_Size = sizeof(char);
    Array_str_size = sizeof(Array_str);

    printf("The size of the 2D Array is %d\n\n", Array_str_size);

    Array_str_num_rows = Array_str_size / sizeof(Array_str[0]);
    Array_str_num_col = sizeof(Array_str[0]) / sizeof(Array_str[0][0]);
    Array_str_num_ele = Array_str_num_rows * Array_str_num_col;


    for (int i = 0; i < Array_str_num_rows; i++)
    {
        isStrLength[i] = Mystrlen(Array_str[i]);
    }

    printf("\n\n");
    printf("Strings in the entire array are:\n\n");
    for (int i = 0; i < Array_str_num_rows; i++)
    {
        printf("String number %d = %s\n", (i + 1), Array_str[i]);
        for (int j = 0; j < isStrLength[i]; j++) 
        {
            printf("Character %d = %c\n", (j + 1), Array_str[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int Mystrlen(char str[])
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
