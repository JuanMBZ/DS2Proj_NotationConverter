#ifndef DSTRUCTS_H
#define DSTRUCTS_H
/***
 *	Place data structure definitions and operations here.
 *
 ***/


#define STACK_SIZE 1000

typedef struct binary_expr_tree {
	struct Token *token;
	struct binary_expr_tree *left_child;
	struct binary_expr_tree *right_child;
} expr_tree;

typedef struct Stack {
	expr_tree **expr_tree_arr;
	int top;
} stack;

expr_tree *create_node(struct Token *t);
stack *create_stack();
void push(stack *s, expr_tree *node);
expr_tree *pop(stack *s);
expr_tree *stack_peek(stack *s);
expr_tree *pop_operator(stack *operator_s, stack *operand_s);

#endif
