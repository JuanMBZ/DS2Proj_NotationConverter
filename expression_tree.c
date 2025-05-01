#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lexer.h"
#include "expression_tree.h"

#ifndef STACK_SIZE
#define STACK 1000
#endif

// Creates a new expression tree node, with token t and NULL children
expr_tree *create_node(struct Token *t){
	expr_tree *node = (expr_tree*) malloc(sizeof(expr_tree));
	node->token = t;
	node->left_child=NULL;
	node->right_child=NULL;

	return node;
}

// Creates a stack of expresion tree nodes with size STACK_SIZE
stack *create_stack() {
	stack *s = (stack*) malloc(sizeof(stack));
	s->expr_tree_arr = (expr_tree**) malloc(sizeof(expr_tree*)*STACK_SIZE);
	(s->expr_tree_arr)[0] = NULL;	//set top of stack to NULL
	s->top = -1;
		
	return s;
}

void push(stack *s, expr_tree *node) {
	// Check for available space in stack
	if((s->top) >= STACK_SIZE) {
		fprintf(stderr, "Stack overflow error, input expression has too many symbols.\n");
		exit(1);
	}

	(s->top)++;
	(s->expr_tree_arr)[s->top] = node;
}

expr_tree *pop(stack *s) {
	// Check if there's something at the top of stack s
	if(s->top < 0) {
		//assert(("Stack underflow error, input expression has missing symbols.\n" && s->top < 0));
		fprintf(stderr, "Stack underflow error, input expression has missing symbols.\n");
		exit(1);
	}
	
	return (s->expr_tree_arr)[(s->top)--];
}

// Returns the top of the stack
expr_tree *stack_peek(stack *s) {
	if(s->top >= 0)
		return (s->expr_tree_arr)[s->top];
	else
		return NULL;
}

// Pops the top of operator stack and assigns the 2 operands from the top of operand stack as right child and left child in that order
// Returns an expression tree node containing the operator and its operand children
expr_tree *pop_operator(stack *operator_s, stack *operand_s) {
	expr_tree *operator = pop(operator_s);
	operator->right_child = pop(operand_s);
	operator->left_child = pop(operand_s);

	return operator;
}

// Creates an expression tree given a valid infix expression input
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
			while((top_op != NULL) && (top_op->token->symbol != '(') && (t->precedence > top_op->token->symbol)) {
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
			while(stack_peek(operator_s)->token->symbol != '(') {
				assert("A right parenthesis had no pairing left parenthesis." && stack_peek(operator_s) != NULL);
				push(operand_s, pop_operator(operator_s, operand_s));
			}
			// Discard the left parenthesis at the top of the stack
			assert("A left parenthesis had no pairing left parenthesis." && stack_peek(operator_s)->token->symbol == '(');
			pop(operator_s);
		}

	} while(t->tok != tok_eof);
	
	//While there are tokens at the top of the stack
	while(stack_peek(operator_s)) {
		assert("A left parenthesis was not closed." && stack_peek(operator_s)->token->symbol != '(');
		push(operand_s, pop_operator(operator_s, operand_s));
	}

	return stack_peek(operand_s);
}

void infix_traversal(expr_tree *root) {
	if(root==NULL)
		return;

	if(!(root->left_child == NULL && root->right_child == NULL))
		printf("(");

	infix_traversal(root->left_child);
	if(root->token->tok == tok_number)
		printf("%d ", root->token->symbol);
	else
		printf("%c ", root->token->symbol);
	infix_traversal(root->right_child);

	if(!(root->left_child == NULL && root->right_child == NULL))
		printf(")");
}
