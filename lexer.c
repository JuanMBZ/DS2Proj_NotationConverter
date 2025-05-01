#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "lexer.h"
#define MAX_DIGITS 9	//Max is 9 because INT_MAX is 10 digits

// Reads the next given token from the input string, automatically moves string pointer to next token
// returns a pointer to a token variable
struct Token* gettok(char **s) {
	struct Token *t;
	t = malloc(sizeof(struct Token));

	while(isspace(**s))
		(*s)++;
	
	char c = **s;
	int offset=1;
	t->symbol = c;
	t->precedence = 0;
	
	//Reads number input using sscanf, stores number of chars read to offset
	if(isdigit(c)) {
		// First check if number of digits is > MAX_DIGITS
		int count=0; char *curr=*s;
		while(isdigit(*curr)) {
			count++; curr++;
		}
		if(count > MAX_DIGITS) {
			fprintf(stderr, "Error: Number input is too large (MAX DIGITS = 9), %s.\n", *s);
			exit(1);
		}

		t->tok = tok_number;
		sscanf(*s, "%d%n", &(t->symbol), &offset);
	}

	else if(c == '+' || c=='-') {
		t->tok = tok_operator;
		t->precedence = 1;
	}

	else if(c == '*' || c=='/') {
		t->tok = tok_operator;
		t->precedence = 2;
	}

	else if(c =='(') {
		t->tok = tok_leftp;
	}

	else if(c ==')')
		t->tok = tok_rightp;

	else if(c == '\0')
		t->tok = tok_eof;
	
	else {
		fprintf(stderr, "Unidentified token '%c' \n", c);
		exit(1);
	}

	(*s) += offset;
	return t;
}
