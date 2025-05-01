#ifndef LEXER_H
#define LEXER_H

enum token_types {
	tok_eof, tok_number, tok_operator,

	// parentheses
	tok_leftp,
	tok_rightp
};

struct Token {
	enum token_types tok;
	int symbol;
	int precedence;
};

struct Token* gettok(char **s);

#endif
