//Tristin Young
//Collyn Lindley
//COP 3402 Systems Software
//Professor Montagne
//Oct 19 2020

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
==============================================================================
This program uses a struct to build the lex table, it is called lexTable and has the lexeme held in a char array lex, the token type held in an int tokType, and an error flag to indicate which error causes held in an int err
==============================================================================
*/

struct lexTable{
	char lex[100];
	int tokType;
	int err;
};

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

	printf("Source Program:\n");
	// Prints the contents of the file
	while((c = fgetc(fp)) != EOF)
		printf("%c", c);

	fclose(fp);
}

// Prints the Lexeme Table with the proper spacing
void printTable(struct lexTable token[], int len)
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\ttoken type\n");
	for (i = 0; i <= len; i++)
		printf("%s\t%d\n", token[i].lex, token[i].tokType);
}

// Prints the Lexeme List with the proper spacing
// ****************************************************************
// needs to implement ascii convertion
void printList(struct lexTable token[], int len)
{
	int i;
	char buff[100];
	printf("Lexeme List:\n");
	for (i = 0; i <= len; i++)
	{
		printf("%d ", token[i].tokType);
		if (token[i].tokType == numbersym)
		{
			//itoa(token[i].lex, buff, 10);
			//printf("%s ", buff);
			printf("%s ", token[i].lex);
		}
		else if (token[i].tokType == identsym)
		{
			printf("%s ", token[i].lex);
		}
	}
	printf("\n");
}

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
	else if (!strcmp(input, ":="))
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

// Processes the file passed through as fName
int procFile(char *fName, struct lexTable token[])
{
	FILE *fp = fopen(fName, "r");

	char buff[1000];
	char buff2[1000];
	int i = 0;
	if (fp == NULL)
	{
		// Prints to std error when file is not opened properly
		fprintf(stderr, "error opening file in printIn");
		return -1;
	}

	// Runs until it finds the end of file
	for (i = 0; !feof(fp); i++)
	{
		fscanf(fp, "%s", buff);
		int len = strlen(buff) - 1;

		if (ispunct(buff[len]) && buff[len] != '=')
		{
			buff2[0] = buff[len];
			buff2[1] = '\0';
			buff[len] = '\0';
			strcpy(token[i].lex, buff);
			token[i].tokType = tokenize(buff);
			i++;
			strcpy(token[i].lex, buff2);
			token[i].tokType = tokenize(buff2);
		}
		else
		{
			strcpy(token[i].lex, buff);
			token[i].tokType = tokenize(buff);
		}

		if (buff2[0] == '.')
		{
			fclose(fp);
			return i;
		}
	}
	fclose(fp);
	return i;
}

int main(int argc, char *argv[])
{
	char *fName = argv[1];
	struct lexTable token[1000];
	int len;
	printIn(fName);
	printf("\n");
	len = procFile(fName, token);
	printTable(token, len);
	printf("\n");
	printList(token, len);

	return 0;
}
