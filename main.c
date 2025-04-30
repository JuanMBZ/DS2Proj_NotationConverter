#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

enum Format {
	infix, prefix, postfix
};

enum token_types {
	tok_eof, tok_number, tok_operator,

	// parentheses
	tok_leftp,
	tok_rightp
};

void print_usage(char *prog_name) {
	fprintf(stderr, "Usage: %s --from <input_format> --to <input_format> \"<expression_string>\" ", prog_name);
	exit(1);
}

int main(int argc, char *argv[]) {
	enum Format in_format, out_format;
	int i;
	struct Token *t;

	for(i=1; i<argc; i++) {

		if(*argv[i] != '-') {
			break;
		}

		// Check user input expression format
		if(strcmp(&(argv[i][1]), "-from") == 0) {      

		if(strcmp(argv[i+1], "infix") == 0)
			in_format=infix;

		else if(strcmp(argv[i+1], "prefix") == 0) 
			in_format=prefix;

		else if(strcmp(argv[i+1], "postfix") == 0)
			in_format=postfix;

		else {
			fprintf(stderr, "Unknown format: --from %s", argv[i+1]);
			exit(1);
		}
		i++;

		}

		if(strcmp(&(argv[i][1]), "-to") == 0) {
			if(strcmp(argv[i+1], "infix") == 0)
				out_format=infix;
			else if(strcmp(argv[i+1], "prefix") == 0) 
				out_format=prefix;
			else if(strcmp(argv[i+1], "postfix") == 0)
				out_format=postfix;
			else {
				fprintf(stderr, "Unknown format: --to %s", argv[i+1]);
				exit(1);
			}
			i++;
		}
	}

	if(i>=argc)
		print_usage(argv[0]);

	printf("Input form=%d, Output form=%d\n", in_format, out_format);
	
	do {
		t = gettok(argv[i]);
		if(t->tok == tok_number) 
			printf("%d, ", t->symbol);
		else
			printf("%d, ", t->tok);
	} while(t->tok != tok_eof);


	return 0;
}
