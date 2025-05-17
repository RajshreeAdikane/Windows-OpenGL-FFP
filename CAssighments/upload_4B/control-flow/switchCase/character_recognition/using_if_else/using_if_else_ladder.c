#include<stdio.h>//for printf()
#include<conio.h>//for getch()

//ASCII VALUE OF A TO Z
#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

//ASCII VALUE OF a to z
#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122

//ASCII VALUE OF 0 TO 9

#define CHAR_DIGIT_BEGINNING 48
#define CHAR_DIGIT_ENDING 57

int main(void)
{
	char ch;
	int ch_value;

	//code
	printf("\n\n");

	printf("Enter the character: \n");
	ch = getch();
	
	if ((ch == 'A' || ch == 'a') || (ch == 'E' || ch == 'e') || (ch == 'I' || ch == 'i') || (ch == 'O' || ch == 'o') || (ch == 'U' || ch == 'u'))
	{
		printf("The Entered Character %c is a VOWEL\n", ch);
	}
	else
	{
		ch_value = (int)ch;
		if (ch_value >= CHAR_ALPHABET_UPPER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_UPPER_CASE_ENDING || (ch_value >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && ch_value <= CHAR_ALPHABET_LOWER_CASE_ENDING))
		{
			printf("Character %c is CONSONENT\n",ch);
		}
		else if (ch_value >= CHAR_DIGIT_BEGINNING && ch_value <= CHAR_DIGIT_ENDING)
		{
			printf("the charecter is %C DIGIT character\n",ch);
		}
		else
		{
			printf("character is %c is SPECIAL character\n", ch);
		}
	}
	return(0);
}