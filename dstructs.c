#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "dstructs.h"
#include "expression_tree.h"

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

// Pops the 2 nodes from stack s and assigns the 2 operands as the operator's right child and left child in that order
// Returns an expression tree node containing the operator and its operand children
expr_tree *assign_operands_to_operator(stack *s, expr_tree *operator) {
	operator->right_child = pop(s);
	operator->left_child = pop(s);

	return operator;
}

