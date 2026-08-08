# Brainfuck Interpreter

A minimal Brainfuck interpreter in C with a bounded tape, precomputed bracket jumps, and live stdin input.

## Why I Built This

Ever since I discovered Brainfuck, I've been as intrigued as I was confused by it. Urban Müller took minimalism to an extreme, and I wanted to understand how he did it.

## Language

Brainfuck is a minimal esoteric programming language. It is Turing complete, but it was not designed for software production; it was meant to be a language with the smallest possible compiler. Its simple design consists of only eight commands, which makes writing and reading programs challenging. The interpreter uses a tape of memory cells, where each cell stores a single byte, and a memory pointer that points to the current cell. The commands manipulate the cells and the pointer.

## Build

```
make
```

Remove the binary with `make clean`.

## Usage

```
./brainfuck            # runs the built-in Hello World
./brainfuck program.bf # runs a program file
```

`,` reads input from stdin at runtime; EOF sets the current cell to zero. Any character outside the eight commands below is ignored.

## Commands

| Command | Effect |
| ------- | ------ |
| `>` | Move the data pointer right. |
| `<` | Move the data pointer left. |
| `+` | Increment the current cell. |
| `-` | Decrement the current cell. |
| `.` | Output the current cell as a character. |
| `,` | Read one byte from stdin into the current cell. |
| `[` | Jump past the matching `]` when the current cell is zero. |
| `]` | Jump back to the matching `[` when the current cell is nonzero. |

Cells hold unsigned bytes and wrap modulo 256. The tape holds 300,000 cells; moving past either end aborts with an error. Unmatched brackets abort with an error.
