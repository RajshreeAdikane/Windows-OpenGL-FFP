#include <stdio.h>
#include <conio.h> // For getch()

int main(void)
{
    int RKA_option, ch = '\0';

    printf("\n\n");
    printf("When the infinite loop begins, enter 'R' or 'r' to quit the loop.\n");
    printf("Enter 'A' or 'a' to start a user-controlled infinite loop.\n");

    RKA_option = getch();
    if (RKA_option == 'A' || RKA_option == 'a')
    {
        do
        {
            printf("You have entered an infinite loop...\n");
            ch = getch();
            if (ch == 'R' || ch == 'r')
                break;
        } while (1);

        printf("\n\n");
        printf("You have controlled the infinite loop.\n");
    }
    else
    {
        printf("You must Press 'A' or 'a' to initiate the loop .....please try again!\n\n");
    }

    return(0);
}
