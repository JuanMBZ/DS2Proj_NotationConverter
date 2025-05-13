#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>

#include "lexer.h"
#include "expression_tree.h"
#include "dstructs.h"

#define GUIDE_FILE "GUIDE.txt"
enum Format {
	infix, prefix, postfix, EMPTY
};

void print_usage(char *prog_name) {
	fprintf(stderr, "Usage: %s [Options] --from <input_format> --to <output_format> \"<expression_string>\"\n", prog_name);
	fprintf(stderr, "   or: %s [Options] <input_format> <output_format> \"<expression_string>\"\n", prog_name);
	fprintf(stderr, "\nExample: %s --evaluate --from infix --to postfix \"1+2-3\"\n", prog_name);
	fprintf(stderr, "          %s --neccessary --evaluate postfix infix \"1 2 + 3 -\"\n", prog_name);
	fprintf(stderr, "\nWhere:\n");
	fprintf(stderr, "   <input_format> and <output_format> = [infix | prefix | postfix]\n");
	fprintf(stderr, "   <expression_string>                = Any valid numerical expression. Numbers can range from [0, 1000000000).\n");
	fprintf(stderr, "                                        Operators are limited to +,-,* and /, (in addition to left and right parenthesis in infix notation).\n"); 
	fprintf(stderr, "\nOptions:\n");
	fprintf(stderr, "   -e, --evaluate         Evaluates the expression and prints the result\n");
	fprintf(stderr, "   -n, --neccessary       Prints an output with INFIX notation with minimal/neccessary parentheses\n");
	fprintf(stderr, "   -h, --help             Display this help text and exit\n");
	fprintf(stderr, "   -g, --guide            Prints the manual for this program\n");
	exit(0);
}

void print_guide() {
	FILE *fptr = fopen(GUIDE_FILE, "r");
	if(fptr == NULL) {
		fprintf(stderr, "Guide file not found make sure you included the 'GUIDE.txt' file from the repository.\n");
		exit(1);
	}
	printf("This guide can be read from the 'GUIDE.txt' file included in the repository.\n\n");
	
	char ch;
	while((ch = fgetc(fptr)) != EOF)
		putchar(ch);

	fclose(fptr);
}

void assign_format(int *format, char *optarg, char **argv) {
	if(strcmp(optarg, "infix") == 0)
		*format=infix;
	else if(strcmp(optarg, "prefix") == 0) 
		*format=prefix;
	else if(strcmp(optarg, "postfix") == 0)
		*format=postfix;
	else {
		fprintf(stderr, "Error: Invalid argument(s).\nUse %s --help to print program usage.\n", argv[0]);
		exit(1);
	}
}

int eval_flag=0;
int neccessary_flag=0;
// Defines the options used for this program
// Passed as argument to getopt_long from <getopt.h>
struct option longopts[] = {
	{"from", required_argument, 0, 'f'},
	{"to", required_argument, 0, 't'},
	{"help", no_argument, 0, 'h'},
	{"guide", no_argument, 0, 'g'},
	/* This option sets flag eval_flag */
	{"evaluate", no_argument, &eval_flag, 1},
	{"neccessary", no_argument, &neccessary_flag, 1},
	{0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
	int in_format=EMPTY, out_format=EMPTY;
	int c;
	expr_tree *root;
	
	// Evaluate user options using getopt_long
	while(1) {
		int option_index=0;			// getopt_long stores current long option (from longopts) here
		c = getopt_long(argc, argv, "hgenf:t:", longopts, &option_index);
		
		if(c == -1)
			break;

		switch(c) {
			//Check case for when getopt_long assigns an eval_flag
			case 0:	//User set an option flag so just continue
				break;
			case 'h':
				print_usage(argv[0]);
				break;
			case 'g':
				print_guide();
				return 0;
			case 'e':
				eval_flag=1;
				break;
			case 'n':
				neccessary_flag=1;
				break;
			case 'f':
				assign_format(&in_format, optarg, argv);
				break;
			case 't':
				assign_format(&out_format, optarg, argv);
				break;
			case '?':
				/* getopt will have already printed the error message so we exit */
				exit(errno);
			default: // Unknown behavior
				fprintf(stderr, "Error: %s, %c.", strerror(EINVAL), c);	// Invalid argument
				exit(EINVAL);
		}
	}
	
	// If user didn't use --from and --to
	if(in_format == EMPTY && out_format == EMPTY) {
		if(optind+1 < argc) {
			assign_format(&in_format, argv[optind], argv);
			assign_format(&out_format, argv[optind+1], argv);
		}
		optind += 2;
	}
	
	//Check for missing required args
	if(optind >= argc) {
		fprintf(stderr, "Error: Missing arguments.\nUse %s --help to print program usage.\n", argv[0]);
		exit(1);
	}

	// Convert argv[i] expression to expression tree from user specified input format
	switch(in_format) {
		case infix:
			root = infix_to_exprtree(argv[optind]);
			break;
		case prefix:
			root = prefix_to_exprtree(argv[optind]);
			break;
		case postfix:
			root = postfix_to_exprtree(argv[optind]);
			break;
		default:
			fprintf(stderr, "Program needs format of both input and output expressions to be specified.\n");
			fprintf(stderr, "Run %s --help to print program usage.\n", argv[0]);
			exit(1);
			break;
	}
	
	switch(out_format) {
		case infix:
			if(neccessary_flag) {
				printf("Expresson tree infix traversal (with minimal parentheses):\n");
				infix_neccessary_traversal(root, root->token);
				printf("\n");
			}
			else {
				printf("Expresson tree infix traversal (with all parentheses):\n");
				infix_traversal(root);
				printf("\n");
			}
			break;
		case prefix:
			printf("Expresson tree prefix traversal:\n");
			prefix_traversal(root);
			printf("\n");
			break;
		case postfix:
			printf("Expression tree postfix traversal:\n");
			postfix_traversal(root);
			printf("\n");
			break;
		default:
			fprintf(stderr, "Program needs format of both input and output expressions to be specified.\n");
			fprintf(stderr, "Run %s --help to print program usage.\n", argv[0]);
			exit(1);
			break;
	}

	if(eval_flag) {
		printf("Expression Evaluation: %d\n", eval_tree(root));
	}
	
	return 0;
}
