main : main.c
	gcc main.c lexer.c expression_tree.c dstructs.c -o ncon -Wall -Wextra -pedantic
