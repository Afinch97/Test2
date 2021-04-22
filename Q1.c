/* front.c - a lexical analyzer system for simple
 arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



/*
char line[1000];
int lineCount = 0;
//char lexeme[100];
char list[200][100];
int listCount = 0;
int i = 0;
*/
void placeToken(char token[]);
void getToken(char linE[], int lineSize);


 /* Global declarations */
 /* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE* in_fp;

/* Function declarations */
int lookup();
int lookupWord();
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define FLOAT 2
#define MINUS 3
#define SCALAR 4
#define ARRAY 5
#define HASH 6
#define STRING 7
#define PREFIX_0 8
#define UNDERSCORE 10
#define UNKNOWN 99

/* Token codes */
#define IDENT 11
#define J_STRING_LIT 12
#define C_INT_LIT 13
#define C_CHAR_LIT 14
#define C_FLOAT_LIT 15
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define MOD_OP 25
#define LOG_AND_OP 26            
#define LOG_OR_OP 27             
#define LOG_NOT_OP 28            
#define OPEN_CODE_BLOCK 29      
#define CLOSE_CODE_BLOCK 30     
#define OPEN_FUNCTION_PARAM 31   
#define CLOSE_FUNCTION_PAREM 32  
#define OPEN_ARRAY_PAREM 33      
#define CLOSE_ARRAY_PAREM 34     
#define PERL_SCALAR 40 
#define PERL_ARRAY 41
#define PERL_HASH 42
#define STRING_TYPE 45          
#define INT_TYPE 46            
#define CHAR_TYPE 47           
#define FLOAT_TYPE 48           
#define VOID_TYPE 49

/******************************************************/
/* main driver */
int main(void) {
	//int* a = malloc(100 * sizeof(int));
	//if (a == NULL) {}
	/* Open the input data file and process its contents */
	if ((in_fp = fopen("front.in", "r")) == NULL)
		printf("ERROR - cannot open front.in \n");
	else {
		getChar();
		do {
			lex();
		} while (nextToken != EOF);
	}
	return 0;
}
/******************************************************/
/* lookup/lookupword - a function to look up operators and
 parentheses and return the token */
int lookup() {
	if (strcmp(lexeme, "=") == 0) {
		nextToken = ASSIGN_OP;
	}
	else if (strcmp(lexeme, "+") == 0) {
		nextToken = ADD_OP;
	}
	else if (strcmp(lexeme, "-") == 0) {
		nextToken = SUB_OP;
	}
	else if (strcmp(lexeme, "*") == 0) {
		nextToken = MULT_OP;
	}
	else if (strcmp(lexeme, "/") == 0) {
		nextToken = DIV_OP;
	}
	else if (strcmp(lexeme, "^") == 0) {
		nextToken = MOD_OP;
	}
	else if (strcmp(lexeme, "##") == 0) {
		nextToken = LOG_AND_OP;
	}
	else if (strcmp(lexeme, "||") == 0) {
		nextToken = LOG_OR_OP;
	}
	else if (strcmp(lexeme, "!") == 0) {
		nextToken = LOG_NOT_OP;
	}
	else if (strcmp(lexeme, "{") == 0) {
		nextToken = OPEN_CODE_BLOCK;
	}
	else if (strcmp(lexeme, "}") == 0) {
		nextToken = CLOSE_CODE_BLOCK;
	}
	else if (strcmp(lexeme, "(") == 0) {
		nextToken = OPEN_FUNCTION_PARAM;
	}
	else if (strcmp(lexeme, ")") == 0) {
		nextToken = CLOSE_FUNCTION_PAREM;
	}
	else if (strcmp(lexeme, "[") == 0) {
		nextToken = OPEN_ARRAY_PAREM;
	}
	else if (strcmp(lexeme, "]") == 0) {
		nextToken = CLOSE_ARRAY_PAREM;
	}
	else {
		nextToken = EOF;
	}
	return nextToken;
}
int lookupWord() {
	if (strcmp(lexeme, "String") == 0) {
		nextToken = STRING_TYPE;
	}
	else if (strcmp(lexeme, "int") == 0) {
		nextToken = INT_TYPE;
	}
	else if (strcmp(lexeme, "Character") == 0) {
		nextToken = CHAR_TYPE;
	}
	else if (strcmp(lexeme, "float") == 0) {
		nextToken = FLOAT_TYPE;
	}
	else if (strcmp(lexeme, "void") == 0) {
		nextToken = VOID_TYPE;
	}
	else {
		nextToken = IDENT;
	}
	return nextToken;
}
/******************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar(void) {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = '\0';
	}
	else
		printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar(void) {
	if ((nextChar = getc(in_fp)) != EOF) {
		if (isalpha(nextChar))
			charClass = LETTER;
	else if (nextChar == '0')
			charClass = PREFIX_0;
		else if (isdigit(nextChar) || nextChar == '.')
			charClass = DIGIT;
	else if (nextChar == '$')
			charClass = SCALAR;
	else if (nextChar == '@')
			charClass = ARRAY;
	else if (nextChar == '%')
			charClass = HASH;
	else if (nextChar == '-')
			charClass = MINUS;
	else if (nextChar == '_')
			charClass = UNDERSCORE;
	else if (nextChar == '"')
			charClass = STRING;
	else if (nextChar)
			charClass = UNKNOWN;
	}
	else
		charClass = EOF;

	// printf("Next Character: %c Next class: %i \n", nextChar, charClass);
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank(void) {
	while (isspace(nextChar))
		getChar();
}

/******************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex(void) {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
		/* Identifiers */
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();
				getChar();
			}
	if (lexLen == 1) {
		nextToken = C_CHAR_LIT;
	}
						else
		lookupWord();
						break;
			/* Integer literals */
			case DIGIT:
		addChar();
		int point = 0;
		if (nextChar == '.') {
			point++;
			}
		if (nextChar == '.') {
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = C_FLOAT_LIT;
			break;
		}
		else if ((charClass == DIGIT) & (nextChar != '.')) {
			getChar();
			printf("digit1 \n");
			addChar();
			getChar();
			while ((charClass == DIGIT) & (nextChar != '.')) {
				printf("digit2 \n");
				addChar();
				getChar();
			}
			if (nextChar == 'e' || nextChar == 'E') {
				addChar();
				getChar();
				if ((charClass == DIGIT) & (nextChar != '.')) {
					addChar();
					getChar();
					while ((charClass == DIGIT) & (nextChar != '.')) {
						addChar();
						getChar();
					}
				}
				else {
					nextToken = EOF;
					break;
				}
				nextToken = C_FLOAT_LIT;
				break;
			}
			if (nextChar == '.') {
					printf("dot \n");
				while (charClass == DIGIT) {
					addChar();
					getChar();
				}
				nextToken = C_FLOAT_LIT;
				printf("cut1 \n");
				break;
			}
			nextToken = C_INT_LIT;
			printf("cut2 \n");
			break;
		}
		nextToken = DIGIT;
						break;
	
	case MINUS:
		addChar();
		point = 0;
				getChar();
		while (charClass == DIGIT) {
			if (nextChar == '.') {
				point++;
			}
						addChar();
						getChar();
					}
		if (lexLen == 1) {
			lookup();
		}
					else {
			if (point == 0) {
				nextToken = C_INT_LIT;
			}
			else if (point == 1) {
				nextToken = C_FLOAT_LIT;
			}
			else {
				nextToken = EOF;
			}
		}
		break;

	/* Perl Scalar Variables */
		case SCALAR:
		getChar();
		while (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE) {
			addChar();
			getChar();
		}
		if (lexLen == 0) {
			nextToken = EOF;
		}
		else
			nextToken = PERL_SCALAR;
		break;

	/* Perl Array Variables */
		case ARRAY:
			getChar();
			while (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE) {
				addChar();
				getChar();
			}
			if (lexLen == 0) {
				nextToken = EOF;
			}
			else
				nextToken = PERL_ARRAY;
			break;

	/* Perl Hash Map Variables */
		case HASH:
			getChar();
			while (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE) {
				addChar();
				getChar();
			}
			if (lexLen == 0) {
				nextToken = EOF;
			}
			else
				nextToken = PERL_HASH;
			break;

		case STRING:
			addChar();
			getChar();
			int closed = 0;
			while ((nextChar != '"') & (charClass == LETTER || charClass == DIGIT || charClass == UNDERSCORE || charClass == UNKNOWN)) {
				addChar();
				getChar();
			}
			if (nextChar == '"') {
				closed = 1;
			}
			if (closed == 0) {
				nextToken = EOF;
			}
			else {
				addChar();
				getChar();
				nextToken = J_STRING_LIT;
			}
			break;

		case PREFIX_0:
			addChar();
			getChar();
			if (nextChar == 'x' || nextChar == 'X') {
				addChar();
				getChar();
				while (charClass == DIGIT || nextChar == 'a' || nextChar == 'b' || nextChar == 'c' || nextChar == 'd' || nextChar == 'e' || nextChar == 'f' || nextChar == 'A' || nextChar == 'B' || nextChar == 'C' || nextChar == 'D' || nextChar == 'E' || nextChar == 'F') {
					addChar();
					getChar();
				}
				if (nextChar == 'L' || nextChar == 'U') {
					addChar();
					getChar();
				}
			}
			else {
				while (nextChar == '0' || nextChar == '1' || nextChar == '2' || nextChar == '3' || nextChar == '4' || nextChar == '5' || nextChar == '6' || nextChar == '7') {
					addChar();
					getChar();
				}
				if (nextChar == 'L' || nextChar == 'U') {
					addChar();
					getChar();
				}
			}
			nextToken = C_INT_LIT;
			break;

	/* Parentheses and operators */
		case UNKNOWN:
			addChar();
			getChar();
			while ((charClass == UNKNOWN) & (isspace(nextChar) == 0)) {
				addChar();
				getChar();
			}
			lookup();
			break;

			/* EOF */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = '\0';
			break;
	 } /* End of switch */

	 printf("Next token is: %d, Next lexeme is %s\n",
		 nextToken, lexeme);
	 return nextToken;
} /* End of function lex */