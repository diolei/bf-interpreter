# Brainfuck Interpreter 
 
This interpreter allows you to provide Brainfuck code, and read its output, as well as, user input via the `*input` pointer.

## Language Overview

Brainfuck is a minimal esoteric programming language that is Turing complete, but wasn't designed for software production, it was meant to be a language with the smallest possible compiler.
It is known for its simplistic design, consisting of only eight commands, which makes it challenging to write and read programs.
A tape of memory cells is used, where each cell can store a single byte of data, and a memory pointer that points to the current cell. The language commands manipulate the memory cells and the memory pointer.

The commands are as follows:
+ `>` Increment the memory pointer, moving it to the next cell.
+ `<` Decrement the memory pointer, moving it to the previous cell.
+ `+` Increment the value in the current memory cell by one.
+ `-` Decrement the value in the current memory cell by one.
+ `.` Output the value in the current memory cell as a character.
+ `,` Accept input from the user and store it in the current memory cell.
+ `[` If the value in the current memory cell is zero, jump forward to the corresponding ] command. Otherwise, continue execution.
+ `]` If the value in the current memory cell is nonzero, jump back to the corresponding [ command. Otherwise, continue execution.


## Compilation

To compile the code, make sure you have `make` installed, and run the following command in the source directory:

```
make
```

## Usage

After compiling the code, just run the `brainfuck` executable, make sure to change the original brainfuck code in the source file as you wish:  

```
./brainfuck
```

## Cleanup

To remove the generated file, you can simply use the following command:

```
make clean
```
