//Tristin Young
//Collyn Lindley
//COP 3402 Systems Software
//Professor Montagne
//Oct 19 2020

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/*
==============================================================================
This program uses a struct to build the lex table, it is called token and has the lexeme held in a char array lex, the token type held in an int tokType, and an error flag to indicate which error causes held in an int err
==============================================================================
*/

struct token{
	char lex[100];
	int tokType;
	int err;
};

typedef enum {
	noletter = INT_MIN, numtoolong, nametoolong, invalidsymbols
} err;

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
		exit(0);
		return;
	}

	printf("Source Program:\n");
	// Prints the contents of the file
	while((c = fgetc(fp)) != EOF)
		printf("%c", c);

	fclose(fp);
}

void printErr(int err)
{
	if (err = noletter)
		printf("Identifier does not start with a letter\n");
	else if (err = numtoolong)
		printf("Number is too long\n");
	else if (err = nametoolong)
		printf("Name is too long\n");
	else if (err = invalidsymbols)
		printf("Invalid symbol\n");
}

// Prints the Lexeme Table with the proper spacing
void printTable(struct token tokens[], int len)
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\ttoken type\n");
	for (i = 0; i < len; i++)
	{
		printf("%s\t", tokens[i].lex);
		if (tokens[i].err)
			printErr(tokens[i].err);
		else
			printf("%d\n", tokens[i].tokType);
	}
}

// Prints the Lexeme List with the proper spacing
// ****************************************************************
// needs to implement ascii convertion
void printList(struct token tokens[], int len)
{
	int i;
	char buff[100];
	printf("Lexeme List:\n");
	for (i = 0; i < len; i++)
	{
		printf("%d ", tokens[i].tokType);
		if (tokens[i].tokType == numbersym)
		{
			//itoa(token[i].lex, buff, 10);
			//printf("%s ", buff);
			printf("%s ", tokens[i].lex);
		}
		else if (tokens[i].tokType == identsym)
		{
			printf("%s ", tokens[i].lex);
		}
	}
	printf("\n");
}

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

int tokenize(char *input)
{
	int i = 0;
	if (input == NULL)
		return nulsym;
	else if (isNumeric(input))
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
	else if (!strcmp(input, "<>"))
		return neqsym;
	else if (!strcmp(input, "<"))
		return lessym;
	else if (!strcmp(input, "<="))
		return leqsym;
	else if (!strcmp(input, ">"))
		return gtrsym;
	else if (!strcmp(input, ">="))
		return geqsym;
	else if (!strcmp(input, "("))
		return lparentsym;
	else if (!strcmp(input, ")"))
		return rparentsym;
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

int isInvalid(char c)
{
	return 0;
}

int checkErr(char *lex, int tType)
{
	if (tType == identsym)
	{
		if (strlen(lex) >= 12)
			return nametoolong;
		else if (isdigit(lex[0]))
			return noletter;
	}
	else if (tType == numbersym)
	{
		if (strlen(lex) >= 6)
			return numtoolong;
	}
	return 0;
}

// Processes the file passed through as fName
int procFile(char *fName, struct token tokens[])
{
	FILE *fp = fopen(fName, "r");

	char cache[1000];
	int c, len = 0, i = 0;
	if (fp == NULL)
	{
		// Prints to std error when file is not opened properly
		fprintf(stderr, "error opening file in procFile");
		exit(0);
		return -1;
	}

	while((c = fgetc(fp)) != EOF)
	{
		i = 0;
		cache[i] = (char) c;
		if (isspace(cache[i]))
		{
			continue;
		}
		else if (cache[i] == '/')
		{
			c = fgetc(fp);
			if ((char)c == '*')
			{
				while (1)
				{
					if ((char) c == '*')
					{
						c = fgetc(fp);
						if ((char) c == '/')
							break;
						fseek(fp, -1, SEEK_CUR);
					}
				}
				continue;
			}
			fseek(fp, -1, SEEK_CUR);
		}
		else if (isInvalid(cache[i]))
		{
			continue;
		}
		else if (cache[i] == ':')
		{
			if ((char)(c = fgetc(fp)) == '=')
				cache[++i] = (char)c;
		}
		else if (isdigit(cache[i]))
		{
			c = fgetc(fp);
			if (isalpha((char)c))
			{
				while(isalpha((char)c))
				{
					cache[++i] = (char)c;
					c = fgetc(fp);
				}
			}
			else
			{
				while(isdigit((char)c))
				{
					cache[++i] = (char)c;
					c = fgetc(fp);
				}
			}
			fseek(fp, -1, SEEK_CUR);
		}
		else if (isalpha(cache[i]))
		{
			c = fgetc(fp);
			while(isalpha((char)c) || isdigit((char)c))
			{
				cache[++i] = (char)c;
				c = fgetc(fp);
			}
			fseek(fp, -1, SEEK_CUR);
		}
		cache[i + 1] = '\0';
		strcpy(tokens[len].lex, cache);
		tokens[len].tokType = tokenize(cache);
		tokens[len].err = checkErr(tokens[len].lex, tokens[len].tokType);
		len++;
		if (cache[0] == '.')
			break;
	}
	fclose(fp);
	return len;
}

int main(int argc, char *argv[])
{
	char *fName = argv[1];
	struct token tokens[1000];
	int len;
	printIn(fName);
	printf("\n");
	len = procFile(fName, tokens);
	printf("\n");
	printTable(tokens, len);
	printf("\n");
	printList(tokens, len);

	return 0;
}
