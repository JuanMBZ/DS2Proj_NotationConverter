#include "dstructs.h"

#ifndef EXPRTREE_H
#define EXPRTREE_H
/***
 *	Place expression tree conversions and traversals here.
 *
 *	Data structure definitions and operations (like create, push, append, etc.) should be in dstructs.h and dstructs.c
 *
 **/

expr_tree *infix_to_exprtree(char *input);
void infix_traversal(expr_tree *root);
void infix_neccessary_traversal(expr_tree *root, struct Token *parent_tok);
expr_tree *prefix_to_exprtree(char *input);  
void prefix_traversal(expr_tree *root);

#endif
