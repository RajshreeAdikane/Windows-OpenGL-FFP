#include <stdio.h>

#define MAX_STRING_LENGTH 512

int Mystrlen(char str[]);

int main(void)
{

    char Array_str[10][15];

    Array_str[0][0] = 'H'; Array_str[0][1] = 'e'; Array_str[0][2] = 'l'; Array_str[0][3] = 'l'; Array_str[0][4] = 'o'; Array_str[0][5] = '!'; Array_str[0][6] = '\0';
    Array_str[1][0] = 'W'; Array_str[1][1] = 'e'; Array_str[1][2] = 'l'; Array_str[1][3] = 'c'; Array_str[1][4] = 'o'; Array_str[1][5] = 'm'; Array_str[1][6] = 'e'; Array_str[1][7] = '\0';
    Array_str[2][0] = 'T'; Array_str[2][1] = 'o'; Array_str[2][2] = '\0';
    Array_str[3][0] = 'A'; Array_str[3][1] = 'M'; Array_str[3][2] = 'C'; Array_str[3][3] = '\0';
    Array_str[4][0] = 'R'; Array_str[4][1] = 'a'; Array_str[4][2] = 'j'; Array_str[4][3] = 'a'; Array_str[4][4] = 's'; Array_str[4][5] = 'h'; Array_str[4][6] = 'r'; Array_str[4][7] = 'e'; Array_str[4][8] = 'e'; Array_str[4][9] = '\0';
    Array_str[5][0] = 'K'; Array_str[5][1] = 'a'; Array_str[5][2] = 's'; Array_str[5][3] = 'h'; Array_str[5][4] = 'i'; Array_str[5][5] = 'n'; Array_str[5][6] = 'a'; Array_str[5][7] = 't'; Array_str[5][8] = 'h'; Array_str[5][9] = '\0';
    Array_str[6][0] = 'A'; Array_str[6][1] = 'd'; Array_str[6][2] = 'i'; Array_str[6][3] = 'k'; Array_str[6][4] = 'a'; Array_str[6][5] = 'n'; Array_str[6][6] = 'e'; Array_str[6][7] = '\0';
    Array_str[7][0] = '2'; Array_str[7][1] = '0'; Array_str[7][2] = '2'; Array_str[7][3] = '4'; Array_str[7][4] = '\0';
    Array_str[8][0] = 'R'; Array_str[8][1] = 'o'; Array_str[8][2] = 'l'; Array_str[8][3] = 'l'; Array_str[8][4] = '_'; Array_str[8][5] = 'n'; Array_str[8][6] = 'o'; Array_str[8][7] = '\0';
    Array_str[9][0] = '0'; Array_str[9][1] = '2'; Array_str[9][2] = '0'; Array_str[9][3] = '\0';

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
