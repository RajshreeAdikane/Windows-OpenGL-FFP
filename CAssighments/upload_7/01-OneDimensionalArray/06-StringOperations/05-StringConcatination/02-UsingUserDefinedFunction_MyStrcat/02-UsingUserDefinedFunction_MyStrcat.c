#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
    void MyStrcat(char des[], char sour[]);

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

    MyStrcat(Array, Array_1);

    printf("The output of the concatenation is: %s\n\n", Array);

    return 0;
}

void MyStrcat(char des[], char sour[])
{
    int MyStrlen(char[]);
    int des_str_length = 0;
    int sour_str_length = 0;

    sour_str_length = MyStrlen(sour);
    des_str_length = MyStrlen(des);


    for(int i = des_str_length, j = 0; j < sour_str_length; i++, j++)
        des[i] = sour[j];
    des[des_str_length + sour_str_length] = '\0';

        
    
}


int MyStrlen(char str[])
{
    int string_length = 0;
    for (int i = 0; i < MAX_STRING_LENGTH; i++)
    {
        if (str[i] == '\0')
            break;
        else
            string_length++;
    }
    return(string_length);

}