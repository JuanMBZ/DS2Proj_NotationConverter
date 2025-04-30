struct b_tree {
	enum Token tok;
	struct b_tree *left_child;
	struct b_tree *right_child;
};

struct stack {
	int top;
	struct b_tree *tree_stack;
}
