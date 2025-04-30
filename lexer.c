#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "lexer.h"

enum token_types {
	tok_eof, tok_number, tok_operator,

	// parentheses
	tok_leftp,
	tok_rightp
};

struct Token {
	enum token_types tok;
	int symbol;
};

struct Token* gettok(char **s) {
	struct Token *t;
	t = malloc(sizeof(struct Token));

	while(isspace(**s))
		(*s)++;
	
	char c = **s;
	int offset=1;
	t->symbol = c;
	
	//Reads number input using sscanf, stores number of chars read to offset
	if(isdigit(c)) {
		t->tok = tok_number;
		sscanf(*s, "%d%n", &(t->symbol), &offset);
	}

	else if(c == '+' || c == '-' || c == '*' || c == '/') {
		t->tok = tok_operator;
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
		exit(0);
	}

	(*s) += offset;
	return t;
}

/*** FOR TESTING
int main() {
	char *test="2147483647 +  234 ()";

	struct Token *t;
	do{
		t=gettok(&test);
		if(t->tok == tok_number)
			printf("%d, ", t->symbol);
		else
			printf("%d, ", t->tok);
			
	} while(t->tok!=tok_eof);
	printf("\n");
	
}
*/
