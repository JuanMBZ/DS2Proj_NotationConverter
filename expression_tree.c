#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lexer.h"
#include "expression_tree.h"
#include "dstructs.h"

#ifndef STACK_SIZE
#define STACK_SIZE 1000
#endif

// Creates an expression tree given a valid infix expression input
// Implements shunting yard algorithm defined in https://en.wikipedia.org/wiki/Shunting_yard_algorithm, with changes to output an expr_tree
// Returns the root node to the expression tree
expr_tree *infix_to_exprtree(char *input) {
	struct Token *t;
	stack *operator_s = create_stack();
	stack *operand_s = create_stack();
	expr_tree *top_op;

	// While there are tokens to be read
	do {
		t = gettok(&input);
		
		// If token is a number, push it into operand stack
		if(t->tok == tok_number) {
			push(operand_s, create_node(t));
		}

		// If token is an operator check precedence
		// No need to check for associativeness since +,-,*,/ are all both left and right associative
		else if(t->tok == tok_operator) {
			// While operator stack is not empty and the top operator is not a left parenthesis, and also current token operator has higher precendence 
			// Pop the operator stack and add push it to operand stack
			top_op = stack_peek(operator_s);
			while(((top_op != NULL) && (top_op->token->symbol != '(')) && (top_op->token->precedence > t->precedence)) {
				push(operand_s, pop_operator(operator_s, operand_s));
				top_op = stack_peek(operator_s);
			}
			// Else push current operator to operator stack
			push(operator_s, create_node(t));
		}
		
		// If token is a left parenthesis then push it into operator stack
		else if(t->tok == tok_leftp) {
			push(operator_s, create_node(t));
		}
		
		// If token is a right parenthesis, pop every operator into operand stack until left parenthesis is found
		else if(t->tok == tok_rightp) {
			while(stack_peek(operator_s) != NULL) {
				// Stop when we see a left parenthesis
				if(stack_peek(operator_s)->token->symbol == '(')
					break;
				push(operand_s, pop_operator(operator_s, operand_s));
			}
			// Make sure the top of the operator is a left parenthesis
			if(stack_peek(operator_s) == NULL) {
				fprintf(stderr, "Error: A right parenthesis had no pairing left parenthesis.\n");
				exit(1);
			}
			// Discard the left parenthesis at the top of the stack
			pop(operator_s);
		}

	} while(t->tok != tok_eof);
	
	//While there are tokens at the top of the stack
	while(stack_peek(operator_s)) {
		assert("A left parenthesis was not closed." && stack_peek(operator_s)->token->symbol != '(');
		// Make sure there is no lone left parenthesis
		if(stack_peek(operator_s)->token->symbol == '(') {
			fprintf(stderr, "Error: A left parenthesis was not closed.\n");
			exit(1);
		}
		push(operand_s, pop_operator(operator_s, operand_s));
	}

	return stack_peek(operand_s);
}

void infix_traversal(expr_tree *root) {
	if(root==NULL)
		return;
	
	// Since all numbers are leaf nodes, check if it is a leaf node before outputting parentheses
	if(!(root->left_child == NULL && root->right_child == NULL))
		printf("(");

	infix_traversal(root->left_child);
	if(root->token->tok == tok_number)
		printf("%d", root->token->symbol);
	else
		printf("%c", root->token->symbol);
	infix_traversal(root->right_child);

	if(!(root->left_child == NULL && root->right_child == NULL))
		printf(")");
}
