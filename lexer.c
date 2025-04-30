#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char *s;

enum tokens {
	tok_eof,

	// num
	tok_number,

	// operator
	tok_operator,

	// parentheses
	tok_leftp,
	tok_rightp
};

struct Token {
	enum tokens tok;
	int symbol;
};

/*
struct b_tree {
	enum Token tok;
	struct b_tree *left_child;
	struct b_tree *right_child;
};

struct stack {
	int top;
	struct b_tree *tree_stack;
}
*/

struct Token* gettok() {
	struct Token *t;
	t = malloc(sizeof(struct Token));

	while(isspace(*s))
		s++;

	if(isdigit(*s)) {
		t->tok = tok_number;
	}

	else if(*s == '+' || *s == '-' || *s == '*' || *s == '/') {
		t->tok = tok_operator;
	}

	else if(*s =='(') {
		t->tok = tok_leftp;
	}

	else if(*s ==')')
		t->tok = tok_rightp;

	else if(*s == '\0')
		t->tok = tok_eof;
	
	else {
		fprintf(stderr, "Unidentified token '%c' \n", *s);
		exit(0);
	}
	s++;
	t->symbol = *s;
	return t;
}

int main() {
	char *test="1 +  1 ()a";
	s=test;
	struct Token *t;
	do{
		t=gettok();
		printf("%d, ", t->tok);
	} while(t->tok!=tok_eof);
	printf("\n");
	
}
