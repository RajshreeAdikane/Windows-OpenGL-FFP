#include <stdio.h>
#include <ctype.h> 

int main() {
    char ch, ch_i;
    unsigned int ascii_ch = 0;

    printf("Enter a character: ");
    scanf("%c", &ch);

    ch = toupper(ch);

    if (ch == 'Q') {
        goto end_program;
    }

    ascii_ch = (unsigned int)ch;
    printf("The ASCII value of '%c' is %u\n", ch, ascii_ch);

    printf("Enter another character (or 'Q' to quit): ");
    scanf(" %c", &ch_i);
    ch = toupper(ch_i);

    if (ch == 'Q') {
        goto end_program;
    }

    ascii_ch = (unsigned int)ch;
    printf("The ASCII value of '%c' is %u\n", ch, ascii_ch);

end_program:
    printf("Program has ended.\n");

    return 0;
}
