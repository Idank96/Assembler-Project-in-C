# Assembler with Two Passes
This is a simple assembler with two passes. It processes input assembly code files, performs two passes, and generates executable files. The assembler uses linked lists for symbol table and memory image data structures. It is designed to handle errors and provide meaningful error messages.

## Usage
To use this assembler, follow these steps:

1. Clone the repository or download the code files.
2. Compile the code using your preferred C compiler (e.g., GCC).
3. Execute the assembler with the input assembly file(s) as arguments.

## Functionality
The assembler performs the following tasks in each pass:

### First Pass
In the first pass, the assembler does the following for each line of code:

Parses the line to identify labels, commands, and operands.
Adds the command and labels to the symbol table (a linked list) if necessary.
Adds the command to the memory image (another linked list).
Checks for errors in the line and continues searching for more errors before proceeding to the second pass.
### Second Pass
In the second pass, the assembler performs the following tasks:

Parses each line again.
Updates the memory image with actual memory addresses for labels and operands.
Generates executable files for each assembly file.

### Error Handling
The assembler is designed to handle errors. If any error is found in the assembly code during the first pass, the assembler will stop processing and display an error message with the line number. The second pass will be skipped, and no executable files will be generated.

2020 assembler project

from: Idan Kogan

- 	To open 'assembler' - open the terminal in 'Maman14' folder and run

- 	The files '.ob' '.ext' '.ent' creates inside the folder 'tests'. 
	Only if you want to change the output folder:
	change the global variable 'dir' from "/tests/" to whatever you want - Inside 'files.c'.
	/*IMPORTANT: create the folder first, then create the '.as' files and then run 'make' command, then run 'assembler'*/

- 	Debug:
- Details on each line: uncomment 'P_All' macro in 'main.c'->'first_pass()'.
	Example:
	cmp K #-6
	op_array[0]: K op_array[1]: -6 
	symbol: command:cmp i_command: 1 i_data: 0 src_rst: dst_rst: label:K opnum1:-999 opnum2:-6src_method:1 dst_method:0


- Details on symbol-table and memory-image: uncomment these functions in 'main.c'->'second_pass()'	printSymbolTable(symbolTable_head);
																												printDataImg(code_head);

Thank you
Idan

