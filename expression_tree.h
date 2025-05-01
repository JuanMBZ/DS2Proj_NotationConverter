#include "dstructs.h"

#ifndef EXPRTREE_H
#define EXPRTREE_H

expr_tree *infix_to_exprtree(char *input);
void infix_traversal(expr_tree *root);

#endif
