//Tristin Young
//Collyn Lindley
//COP 3402 Systems Software
//Professor Montagne
//Oct 19 2020

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
==============================================================================
Possible executions:
1) store token type, meaning tokenize only get called to tokenize the lexeme when reading the file and then can be printed later on
2) dont store token type, meaning tokenize will have to be called every time we need to print the token type
==============================================================================

IDK where i stand, i need to think more on it -collyn

*/

typedef enum {
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym,
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym } token_type;

// Prints the input file from the command line, char *fName
// Prints error and exits program if file not opened properly
void printIn(char *fName)
{
	FILE *fp = fopen(fName, "r");
	int c = 0;
	if (fp == NULL)
	{
		// Prints to std error when file is not opened properly
		fprintf(stderr, "error opening file in printIn");
		return;
	}

	// Prints the contents of the file
	while((c = fgetc(fp)) != EOF)
		printf("%c", c);

	fclose(fp);
}

void printLexTable(char *lex, int token)

int tokenize(char *input)
{
	//printf("tokenize function\n");
	//fflush(stdout);
	//if (input == NULL)
	//	return nulsym;
	if (isdigit(*input) != 0)
		return numbersym;
	else if (!strcmp(input, "+"))
		return plussym;
	else if (!strcmp(input, "-"))
		return minussym;
	else if (!strcmp(input, "*"))
		return multsym;
	else if (!strcmp(input, "/"))
		return slashsym;
	else if (!strcmp(input, "odd"))
		return oddsym;
	else if (!strcmp(input, "="))
		return eqsym;
	else if (!strcmp(input, "!="))
		return neqsym;
	else if (!strcmp(input, "<"))
		return lessym;
	else if (!strcmp(input, "<="))
		return leqsym;
	else if (!strcmp(input, ">"))
		return gtrsym;
	else if (!strcmp(input, ">="))
		return geqsym;
	//else if (input == ???)
	//	return lparentsym;
	//else if (input == ???)
	//	return rparentsym;
	else if (!strcmp(input, ","))
		return commasym;
	else if (!strcmp(input, ";"))
		return semicolonsym;
	else if (!strcmp(input, "."))
		return periodsym;
	else if (!strcmp(input, "becomes"))
		return becomessym;
	else if (!strcmp(input, "begin"))
		return beginsym;
	else if (!strcmp(input, "end"))
		return endsym;
	else if (!strcmp(input, "if"))
		return ifsym;
	else if (!strcmp(input, "then"))
		return thensym;
	else if (!strcmp(input, "while"))
		return whilesym;
	else if (!strcmp(input, "do"))
		return dosym;
	else if (!strcmp(input, "call"))
		return callsym;
	else if (!strcmp(input, "const"))
		return constsym;
	else if (!strcmp(input, "var"))
		return varsym;
	else if (!strcmp(input, "proc"))
		return procsym;
	else if (!strcmp(input, "write"))
		return writesym;
	else if (!strcmp(input, "read"))
		return readsym;
	else if (!strcmp(input, "else"))
		return elsesym;
	else
		return identsym;
}

// Processes the file passed through fName
void procFile(char *fName)
{
	FILE *fp = fopen(fName, "r");
	int c = 0;
	char buff[1000];
	//needs to be "global", lexeme and lexList
	char *lexeme[1000];
	int lexList [1000];
	int i = 0;
	if (fp == NULL)
	{
		// Prints to std error when file is not opened properly
		fprintf(stderr, "error opening file in printIn");
		return;
	}

	// Runs until it finds the end of file
	while (!feof(fp))
	{
		fscanf(fp, "%s", buff);
		lexeme[i] = buff;
		printf("%s ", lexeme[i]);
		fflush(stdout);

		//This will be dynamic just not yet
		lexList[i] = tokenize(buff);

		/*
		**************************************************************
		Need this, will split the string at any given point:
		strtok(string, " ")
		**************************************************************
		*/

		printf("%d\n", lexList[i]);
		i++;
	}


	fclose(fp);
}

int main(int argc, char *argv[])
{
	char *fName = argv[1];
	printIn(fName);
	procFile(fName);

	return 0;
}
