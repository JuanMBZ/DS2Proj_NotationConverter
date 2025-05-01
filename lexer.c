#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "lexer.h"

// Reads the next given token from the input string, automatically moves pointer to string
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
