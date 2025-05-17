#include <stdio.h>
#include <conio.h> // For getch()

int main(void)
{
    int RKA_option, ch = '\0';

    printf("\n\n");
    printf("When the infinite loop begins, enter 'R' or 'r' to quit the loop.\n");
    do
    {
        do
        {
            printf("You have entered an infinite loop...\n");
            ch = getch();

        } while (ch != 'R' && ch != 'r');
        printf("\n\n");
        printf("you are exiting in thte loop");

        printf("\n\n");
        printf("Do you want to begin the loop again ('A' or 'a' for yes any other key for No )");
        RKA_option = getch();

    } while (RKA_option == 'A' || RKA_option == 'a');

    printf("\n\n");
    printf("You have controlled the infinite loop.\n");

    return(0);
}
