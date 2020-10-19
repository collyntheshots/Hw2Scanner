// Collyn Lindley
// Tristin Young

#include <stdio.h>

typedef enum {
nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
multsym = 6,  slashsym = 7, oddsym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18,
periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24,
whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
readsym  = 32, elsesym = 33 } token_type;

int lexList [1000];

// Prints the input file from the command line, char in[]
// Prints error and exits program if file not opened properly
void printIn(char in[])
{
	FILE *fp = fopen(in, "r");
	int c = 0;
	if (fp == NULL)
	{
		fprintf(stderr, "error opening file in printIn");
		return;
	}

	while((c = fgetc(fp)) != EOF)
		printf("%c", c);

	fclose(fp);
}

int main(int argc, char *argv[])
{
	printIn(argv[1]);
	return 0;
}
