# DS2Proj_NotationConverter
Project for CS110 - Discrete Structures 2. CLI Utility Program to convert numerical expression input to desired output notation.

## Compiling 
-To compile the Program, use any terminal(GNOME Terminal, PowerShell, Command Prompt)
If your system have the make program, just type:
>make
Otherwise, run with gcc:
>gcc main.c lexer.c expression_tree.c dstructs.c -o ncon -Wall -Wextra -pedantic

## Running
-To run the program, make sure there were no errors when compiling. 
The program is called like this: 
>./ncon [Options] \<expression\>

On linux systems

Example:
>./ncon --from infix --to prefix "12 + 34 * (87 / 86 - (23-1))"
>./ncon --from prefix --to postfix "* / - + 1 4 5 6 7 "

The valid formats for running are: 

./ncon
[Options] = --from infix --to prefix
            --from infix --to postfix
            --from prefix --to infix
            --from prefix --to postfix
            --from postfix --to infix
            --from postfix --to prefix
\<expression\>
Note:  -The program only support ADDITION(+), SUBTRACTION(-), MULTIPLICATION(*), and DIVISION(/) operators.It assumes standard precedence where * , / is higher than +, -
        and left-to-right associativity for operators of the same precedence.
        -The expression must be enclosed by a QOUTATION MARK("").

If the <input_format> is infix, the expression must be on infix notation, or
        --from infix --to prefix " (1 + 2) * 3"
    the <input_format> is prefix, the expression must be on prefix notation, or
        --from prefix --to posfix " - 1 2"
    the <input_format> is postfix, the expression must be on postfix notation. 
        --from postfix --to infix " 1 2 /"


## Terminologies:
Terminal - A terminal is a text-based interface where users can interact with the operating system or run software programs by typing commands.
Expression Notation - refers to how mathematical or logical expressions are written - particularly in the context of operations (like addition, multiplication, etc.)
                      and operands (the values they act on).
        Types of Notations
        1. Infix Notation - It is the most common and human-readable format. The operator is placed between the operands.
                          - Requires parentheses to clarify the order of the operations(precedence). 
                          - Evaluation is done on operator precedence and associativity.
                            Example:
                                    A + B , (A - B) + C
                                    1 + 2, (12 - 6) + 7
        2. Prefix Notation(Polish Notation) - Operator comes before the operands. No need for parentheses, as the structure defines the order.
                            Example: 
                                   * + A B C
                                   * + 2 4 6, which is same as (2 + 4) * 6 in infix notation
        3. Postfix Notation(Reverse Polish Notation) - Operator comes after the operands. It also doesn't need parentheses as the structure defines the order.
                            Example: 
                                    A B + C *
                                    2 4 + 6 *, which is same as (2 + 4) * 6 in infix notation

