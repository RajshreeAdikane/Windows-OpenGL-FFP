#include <stdio.h>

#define MAX_STRING_LENGTH 512

int Mystrlen(char str[]);

int main(void)
{
    char Array_str[10][15];
    snprintf(Array_str[0], 15, "Hello!");
    snprintf(Array_str[1], 15, "Welcome");
    snprintf(Array_str[2], 15, "To");
    snprintf(Array_str[3], 15, "AMC");
    snprintf(Array_str[4], 15, "Rajashree");
    snprintf(Array_str[5], 15, "Kashinath");
    snprintf(Array_str[6], 15, "Adikane");
    snprintf(Array_str[7], 15, "2024");
    snprintf(Array_str[8], 15, "Roll_no");
    snprintf(Array_str[9], 15, "020");

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
        printf("%s\n", Array_str[i]);
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
