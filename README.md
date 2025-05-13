# DS2Proj_NotationConverter
Project for CS110 - Discrete Structures 2. CLI Utility Program to convert numerical expression input to desired output notation.

## Requirements
OS: Linux (Recommended), Windows 11
Programs: 
- gcc (Latest version)
- GNU make [Optional]
- git [Optional]

## Compiling 
Use any terminal(GNOME Terminal, PowerShell, Command Prompt) your system has to perform the following actions.
Download the source code either by using git:
> git clone https://github.com/JuanMBZ/DS2Proj_NotationConverter.git

Or by directly downloading the source files from this repository.

To compile (assuming gcc is already in your system) with make, just run:
> make  

Otherwise, run with gcc:  
> gcc main.c lexer.c expression_tree.c dstructs.c -o ncon -Wall -Wextra -pedantic  

## Documentation
Instructions on program usage can be seen by running:
> ./ncon --help

More specific explainations on program options and how the program works can be seen by opening the GUIDE.txt file or by running:
> ./ncon --guide


## Program Details
The whole program is written in the C language, and its only dependency is the Standard C Library.
The program was designed with simplicity and with the aim to learn fundamental data structures in mind. Thus all data structures and operations were defined based on program needs and from past lessons.

Limitations of the program include:
1. No built-in functionality for other operators such as unary operators, the exponent operator(^), the modulo operator(%), functions, etc.
2. Since C doesn't offer much options for error-handling like C++, Java or Python, error-handling in this program does not go too in-depth, but is still provides sufficient information to be understood.
3. Only tested for the latest Linux kernel and Windows 11 so there is no assurance for other OS. Program was also only compiled for the latest version of gcc.
