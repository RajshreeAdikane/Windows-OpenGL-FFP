#include <stdio.h>

int main(void)
{
    int RKA_num, RKA_num1;

    printf("\n\n");

    printf("Enter any RKA_number: ");
    scanf("%d", &RKA_num);

    printf("Enter the digits you want to print from %d onwards: ", RKA_num);
    scanf("%d", &RKA_num1);

    printf("Printing digits %d to %d\n\n", RKA_num, RKA_num + RKA_num1);

    int i = RKA_num;
    do
    {
        printf("\t%d\n", i);
        i++;
    } while (i <= (RKA_num + RKA_num1));

    return (0);
}
