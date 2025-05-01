#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "expression_tree.h"
#include "dstructs.h"

enum Format {
	infix, prefix, postfix, EMPTY
};

void print_usage(char *prog_name) {
	fprintf(stderr, "Usage: %s --from <input_format> --to <output_format> \"<expression_string>\"\n", prog_name);
	fprintf(stderr, "Input and output formats: infix, prefix, or postfix.\n");
	exit(1);
}

int main(int argc, char *argv[]) {
	int in_format=EMPTY, out_format=EMPTY;
	int i;
	expr_tree *root;
	//struct Token *t, *curr_tok;	//For testing
	
	// For loop to check all user [Options] entered
	// Manual parser for arguments, since getopts(3) can't handle long options
	for(i=1; i<argc; i++) {

		//Checks if current argv has a '-' prefix
		if(*argv[i] != '-') {
			break;
		}

		// Read user input/output expression format
		if(strcmp(&(argv[i][1]), "-from") == 0) {      

			if(strcmp(argv[i+1], "infix") == 0)
				in_format=infix;
			else if(strcmp(argv[i+1], "prefix") == 0) 
				in_format=prefix;
			else if(strcmp(argv[i+1], "postfix") == 0)
				in_format=postfix;
			else {
				fprintf(stderr, "Unknown format: --from %s\n", argv[i+1]);
				exit(1);
			}
			// Move to next arg
			i++;
		}

		// Read user output expression format
		else if(strcmp(&(argv[i][1]), "-to") == 0) {

			if(strcmp(argv[i+1], "infix") == 0)
				out_format=infix;
			else if(strcmp(argv[i+1], "prefix") == 0) 
				out_format=prefix;
			else if(strcmp(argv[i+1], "postfix") == 0)
				out_format=postfix;
			else {
				fprintf(stderr, "Unknown format: --to %s\n", argv[i+1]);
				exit(1);
			}
			// Move to next arg
			i++;
		}

		else if(strcmp(&(argv[i][1]), "-help") == 0) {
			print_usage(argv[0]);
		}

		else {
			fprintf(stderr, "Run %s --help to print program usage.\n", argv[0]);
			exit(1);
		}
	}

	// Check for missing arguments
	if(i>=argc) {
		fprintf(stderr, "Missing arguments.\n");
		fprintf(stderr, "Run %s --help to print program usage.\n", argv[0]);
		exit(1);
	}
	
	//Checks if user inputted missing formats
	if(in_format == EMPTY || out_format == EMPTY) {
		fprintf(stderr, "Program needs format of input and output expressions to be specified.\n");
		fprintf(stderr, "Run %s --help to print program usage.\n", argv[0]);
		exit(1);
	}
	
	// Convert argv[i] expression to expression tree from user specified input format
	switch(in_format) {
		case infix:
			root = infix_to_exprtree(argv[i]);
			break;
		case prefix:
			root = prefix_to_exprtree(argv[i]);
			break;
		case postfix:
			// Palagay nalang dito ng <format> to tree function
			// Nasa argv[i] nakalagay ang expression, kaya kailangan yun isabay sa arguments ng inyong function
			break;
		default:
			break;
	}

	switch(out_format) {
		case infix:
			printf("Expresson tree infix Traversal:\n");
			infix_traversal(root);
			printf("\n");
			break;
		case prefix:
			printf("Expresson tree infix Traversal:\n");
			prefix_traversal(root);
			printf("\n");
			break;
		case postfix:
			break;
		default:
			break;
	}
	
	return 0;
}
