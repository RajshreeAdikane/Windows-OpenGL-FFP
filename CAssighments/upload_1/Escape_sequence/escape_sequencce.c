#include <stdio.h> 

int main(void) {
    // codeD
    printf("Going to next line \\n Escape Sequences in C:\n\n");
    printf("Demonstrating \t Horizontal \t Tab \t using \\t Escape sequence !!! \n\n");
    printf("\"This is the double quoted output\" done using \\\" \\\" escape sequence\n\n");
    printf("\'This is the single quoted output\' done using \\\' \\\' escape sequence \n\n");
    printf("Backspace turned to Backspace\b using escape sequence \\b \n\n");
    printf("\rDemonstrating carriage return \\r escape sequence\n");
    printf("Demonstrating \r carriage return using \\r escape sequence\n");
    printf("Demonstrating carriage \r return using \\r escape sequence\n");

    printf("Demonstrating \x41 using \\xhh escape sequence\n");
    printf("Demonstating \102 using \\ooo escape sequencce \n\n");

    return 0;
}
